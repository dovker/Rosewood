#pragma once
#include "rwpch.h"
#include "Observer.h"
#include "SignalTypes.h"
#include "Rosewood/Core/Types.h"

namespace Rosewood
{
    struct Signal
    {
        SignalCategory Category;
        uint32_t Type; //Allows to be user defined for simplicity
        //Maybe STD::INITIALIZER LIST?
        union Data
        {
            float Float[8];
            
            uint8_t  Uint8[32];
            uint16_t Uint16[16];
            uint32_t Uint32[8];
            uint64_t Uint64[4];

            int8_t  Int8[32];
            int16_t Int16[16];
            int32_t Int32[8];
            int64_t Int64[4];
            
            char Char[32];
            
            UnsafeBuffer Buffer;
            std::any Object;
        }; //32 bytes
    };

    class Subject
    {
    public:
        void Subscribe(Observer* observer)
        {
            m_Observers.push_back(observer);
        }
        void Unsubscribe(Observer* observer)
        {
            int i = 0;
            for(auto o : m_Observers)
            {
                if(o == observer)
                {
                    m_Observers.erase(i);
                    return;
                }
                o++;
            }
        }
    protected:
        void Notify(std::any& sender, Signal signal)
        {
            for(auto o : m_Observers)
            {
                o->OnNotify(sender, signal);
            }
        }
    private:
        std::vector<Observer*> m_Observers;
        //LATER HANDLE THIS ON AN UPDATE LOOP
    };
}