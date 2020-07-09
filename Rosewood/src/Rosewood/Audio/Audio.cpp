/*#include "rwpch.h"
#include "Audio.h"

#include <stdio.h>
#include <stdlib.h>

#include "AL/al.h"
#include "AL/alext.h"
#include "alc/alcmain.h"
#include "alhelpers.h"

#define MINIMP3_IMPLEMENTATION
#include "minimp3.h"
#include "minimp3_ex.h"


namespace Rosewood {

    static ALCdevice* s_AudioDevice = nullptr;
    static mp3dec_t s_Mp3d;

    static uint8_t* s_AudioScratchBuffer;
    static uint32_t s_AudioScratchBufferSize = 10 * 1024 * 1024; // 10mb initially

    static bool s_DebugLog = true;

#define HA_LOG(x) std::cout << "[Hazel Audio]  " << x << std::endl

    // Currently supported file formats
    enum class AudioFileFormat
    {
        None = 0,
        MP3
    };

    static AudioFileFormat GetFileFormat(const std::string& filename)
    {
        std::filesystem::path path = filename;
        std::string extension = path.extension().string();

        if (extension == ".mp3")  return AudioFileFormat::MP3;
        
        return AudioFileFormat::None;
    }

    static ALenum GetOpenALFormat(uint32_t channels)
    {
        // Note: sample size is always 2 bytes (16-bits) with
        // both the .mp3 and .ogg decoders that we're using
        switch (channels)
        {
            case 1:  return AL_FORMAT_MONO16;
            case 2:  return AL_FORMAT_STEREO16;
        }
        // assert
        return 0;
    }

    

    Sound Audio::LoadAudioSourceMP3(const std::string& filename)
    {
        mp3dec_file_info_t info;
        int loadResult = mp3dec_load(&s_Mp3d, filename.c_str(), &info, NULL, NULL);
        uint32_t size = info.samples * sizeof(mp3d_sample_t);

        auto sampleRate = info.hz;
        auto channels = info.channels;
        auto alFormat = GetOpenALFormat(channels);
        float lengthSeconds = size / (info.avg_bitrate_kbps * 1024.0f);

        ALuint buffer;
        alGenBuffers(1, &buffer);
        alBufferData(buffer, alFormat, info.buffer, size, sampleRate);

        Sound result = { buffer, true, lengthSeconds };
        alGenSources(1, &result.m_SourceHandle);
        alSourcei(result.m_SourceHandle, AL_BUFFER, buffer);

        if (s_DebugLog)
        {
            RW_CORE_INFO("File Info - {0} :", filename);
            RW_CORE_INFO("  Channels: {0}", channels);
            RW_CORE_INFO("  Sample Rate: {0}", sampleRate);
            RW_CORE_INFO("  Size: {0} bytes", size);

            auto [mins, secs] = result.GetLengthMinutesAndSeconds();
            HA_LOG("  Length: " << mins << "m" << secs << "s");
        }

        if (alGetError() != AL_NO_ERROR)
            std::cout << "Failed to setup sound source" << std::endl;

        return result;
    }

    static void PrintAudioDeviceInfo()
    {
        if (s_DebugLog)
        {
            RW_CORE_INFO("Audio Device Info:");
            RW_CORE_INFO("  Name: {0}", s_AudioDevice->DeviceName);
            RW_CORE_INFO("  Sample Rate: {0}", s_AudioDevice->Frequency);
            RW_CORE_INFO("  Max Sources: {0}", s_AudioDevice->SourcesMax);
            RW_CORE_INFO("    Mono: {0}", s_AudioDevice->NumMonoSources);
            RW_CORE_INFO("    Stereo: {0}", s_AudioDevice->NumStereoSources);
        }
    }

    void Audio::Init()
    {
        if (InitAL(s_AudioDevice, nullptr, 0) != 0)
            std::cout << "Audio device error!\n";

        PrintAudioDeviceInfo();

        mp3dec_init(&s_Mp3d);

        s_AudioScratchBuffer = new uint8_t[s_AudioScratchBufferSize];

        // Init listener
        ALfloat listenerPos[] = { 0.0,0.0,0.0 };
        ALfloat listenerVel[] = { 0.0,0.0,0.0 };
        ALfloat listenerOri[] = { 0.0,0.0,-1.0, 0.0,1.0,0.0 };
        alListenerfv(AL_POSITION, listenerPos);
        alListenerfv(AL_VELOCITY, listenerVel);
        alListenerfv(AL_ORIENTATION, listenerOri);
    }

    Sound Audio::LoadAudioSource(const std::string& filename)
    {
        auto format = GetFileFormat(filename);
        switch (format)
        {
            case AudioFileFormat::MP3:  return LoadAudioSourceMP3(filename);
        }

        // Loading failed or unsupported file type
        return { 0, false, 0 };
    }
    
    void Audio::Play(const Sound& sound)
    {
        // Play the sound until it finishes
        alSourcePlay(sound.m_SourceHandle);

        // TODO: current playback time and playback finished callback
        // eg.
        // ALfloat offset;
        // alGetSourcei(audioSource.m_SourceHandle, AL_SOURCE_STATE, &s_PlayState);
        // ALenum s_PlayState;
        // alGetSourcef(audioSource.m_SourceHandle, AL_SEC_OFFSET, &offset);
    }

    void Audio::SetDebugLogging(bool log)
    {
        s_DebugLog = log;
    }

    Sound::Sound(uint32_t handle, bool loaded, float length)
        : m_BufferHandle(handle), m_Loaded(loaded), m_TotalDuration(length)
    {
    }

    Sound::~Sound()
    {
        // TODO: free openal audio source?
    }

    void Sound::SetPosition(float x, float y, float z)
    {
        //alSource3f(source, AL_VELOCITY, 0, 0, 0);

        m_Position[0] = x;
        m_Position[1] = y;
        m_Position[2] = z;

        alSourcefv(m_SourceHandle, AL_POSITION, m_Position);
    }

    void Sound::SetGain(float gain)
    {
        m_Gain = gain;

        alSourcef(m_SourceHandle, AL_GAIN, gain);
    }

    void Sound::SetPitch(float pitch)
    {
        m_Pitch = pitch;

        alSourcef(m_SourceHandle, AL_PITCH, pitch);
    }

    void Sound::SetSpatial(bool spatial)
    {
        m_Spatial = spatial;

        alSourcei(m_SourceHandle, AL_SOURCE_SPATIALIZE_SOFT, spatial ? AL_TRUE : AL_FALSE);
        alDistanceModel(AL_INVERSE_DISTANCE_CLAMPED);
    }

    void Sound::SetLoop(bool loop)
    {
        m_Loop = loop;

        alSourcei(m_SourceHandle, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);
    }

    std::pair<uint32_t, uint32_t> Sound::GetLengthMinutesAndSeconds() const
    {
        return { (uint32_t)(m_TotalDuration / 60.0f), (uint32_t)m_TotalDuration % 60 };
    }

    Sound Sound::LoadFromFile(const std::string& file, bool spatial)
    {
        Sound result = Audio::LoadAudioSource(file);
        result.SetSpatial(spatial);
        return result;
    }

}
*/