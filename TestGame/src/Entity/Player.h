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
        void OnLoad() override;
        void OnUpdate() override;
        void OnDraw() override;
        void OnUnload() override;

    private:
        glm::vec3 m_Position;
    };
}
