#pragma once

#include "../Game.h"

namespace TestGame
{
    class Entity
    {
    public:
        Entity() { m_Visible = true; };
        ~Entity(){};
        virtual void OnLoad()   {};
        virtual void OnUpdate() {};
        virtual void OnDraw()   {};
        virtual void OnUnload() {};
    private:
        bool m_Visible;
    };
}
