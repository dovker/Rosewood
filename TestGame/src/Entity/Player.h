#pragma once

#include "Entity.h"
#include "../Game.h"

namespace TestGame
{
    class Player : public Entity
    {
    public:
        Player();
        ~Player();
        virtual void OnLoad()   override;
        virtual void OnUpdate() override;
        virtual void OnDraw()   override;
        virtual void OnUnload() override;

    private:
        glm::vec3 m_Position;
    };
}
