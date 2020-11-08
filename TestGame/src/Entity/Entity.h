#pragma once

#include "../Game.h"

namespace TestGame
{
    class Entity
    {
    public:
        Entity() { m_Visible = true; };
        ~Entity(){};
        virtual void OnLoad() = 0;
        virtual void OnUpdate() = 0;
        virtual void OnDraw() = 0;
        virtual void OnUnload() = 0;
    private:
        bool m_Visible;
    };
}
