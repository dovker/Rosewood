#pragma once
#include "Rosewood.h"
#include "../Entity/Entity.h"
#include "../Collision/Collision.h"
#include "../Map/Map.h"

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

        void SetMap(Map* map) { m_Map = map; }

    private:
        Rosewood::Sprite m_SpriteAnim;
        Rosewood::Rect m_Collider;
        glm::vec2 m_Velocity;
        glm::vec2 m_Acceleration;
        Map* m_Map;

        void CalculateMovement();
        void CalculateCollisions(float dt, std::vector<Entity*> entities);
        void ResolveStaticCollisions(float dt, std::vector<std::pair<Rosewood::Rect, float>> rects);

    };
}
