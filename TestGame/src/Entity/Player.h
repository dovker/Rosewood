#pragma once
#include "Rosewood.h"
#include "../Entity/Entity.h"
#include "../Collision/Collision.h"
#include "../Scene/Scene.h"
#include <glm/glm.hpp>


namespace TestGame
{
    class Player : public Entity
    {
    public:
        Player();
        virtual void OnLoad()   override;
        virtual void OnUpdate(float dt, std::vector<Entity*> entities) override;
        virtual void OnDraw()   override;
        virtual void OnUnload() override;
        virtual void OnEvent(Rosewood::Event &e) override;

    private:
        Rosewood::Ref<Rosewood::Sprite> m_SpriteAnim;
        Rosewood::Rect m_Collider;
    };
}
