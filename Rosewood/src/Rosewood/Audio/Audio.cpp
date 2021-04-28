#include "rwpch.h"
#include "Audio.h"

#include <stdio.h>
#include <stdlib.h>



namespace Rosewood {

    static Scope<SoLoud::Soloud> s_AudioDevice;

    void Audio::Init()
    {
        s_AudioDevice = CreateScope<SoLoud::Soloud>();
        s_AudioDevice->init();
    }
    void Audio::Deinit()
    {
        s_AudioDevice->deinit();
    }
    float Audio::GetGlobalVolume()
    {
        return s_AudioDevice->getGlobalVolume();
    }
    void Audio::SetGlobalVolume(float volume)
    {
        s_AudioDevice->setGlobalVolume(volume);
    }
    
    void Audio::StopAll()
    {
        s_AudioDevice->stopAll();
    }






    Sound::Sound(const std::string& path)
        : m_Path(path)
    {
        m_Sound.load(path.c_str());
    }
    
    Ref<Sound> Sound::Create(const std::string& path)
    {
        return CreateRef<Sound>(path);
    }

    void Sound::Play()
    {
        m_Handle = s_AudioDevice->play(m_Sound, m_Volume, m_Pan, m_Paused);
        
        s_AudioDevice->setProtectVoice(m_Handle, m_Protected);
    }
    void Sound::PlayBackground()
    {
        m_Handle = s_AudioDevice->playBackground(m_Sound, m_Volume, m_Paused);
        s_AudioDevice->setProtectVoice(m_Handle, m_Protected);
    }

    void Sound::Stop()
    {
        m_Sound.stop();
    }


    double Sound::GetLength()
    {
        return m_Sound.getLength();
    }




    void Sound::SetLooping(bool looping)
    {
        m_Looping = looping;
        m_Sound.setLooping(m_Looping);
    }

    void Sound::SetVolume(float volume)
    {
        m_Volume = volume;
        m_Sound.setVolume(m_Volume);
    }
    
    void Sound::SetProtected(bool prot)
    {
        m_Protected = prot;
    }
    void Sound::SetPause(bool pause)
    {
        m_Paused = pause;
        s_AudioDevice->setPause(m_Handle, m_Paused);
    }
    void Sound::SetPan(float pan)
    {
        m_Pan = pan;
        s_AudioDevice->setPan(m_Handle, m_Pan);
    }


    void Sound::SetSpeed(float speed)
    {
        s_AudioDevice->setRelativePlaySpeed(m_Handle, speed);
    }
}
