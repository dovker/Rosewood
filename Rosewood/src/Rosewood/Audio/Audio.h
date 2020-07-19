#pragma once
#include "rwpch.h"

#include "soloud.h"
#include "soloud_speech.h"
#include "soloud_thread.h"
#include "soloud_wav.h"


namespace Rosewood {

    class Sound
    {
    public:
        ~Sound() {}
        Sound();
        Sound(const std::string& path);
        
        void Play();
        void PlayBackground();

        void Stop();
        
        double GetLength();
        float GetVolume() {return m_Volume;}
        
        
        //TODO: Pitch, 3D, Filters, protect so on.
        //TODO: Faders and Filters

        //CHANGED ANY TIME
        void SetLooping(bool looping);
        void SetProtected(bool prot);
        void SetVolume(float volume);
        
        //CHANGED AFTER PLAYING
        void SetPan(float pan);
        void SetSpeed(float speed);
        void SetPause(bool pause);

        static Ref<Sound> Create(const std::string& path);
    
    private:
        int m_Handle;
        bool m_Paused = false;
        bool m_Looping = false;
        bool m_Protected = false;
        float m_Volume = 1.0f;
        float m_Pan = 0.0f;
        
        SoLoud::Wav m_Sound;
    };

    class Audio
    {
    public:
        static void Init();
        static void Deinit();
        
        static float GetGlobalVolume();
        static void SetGlobalVolume(float volume);
        
        static void StopAll();
    };

}

