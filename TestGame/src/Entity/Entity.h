#pragma once
#include "Rosewood.h"
#include <glm/glm.hpp>


namespace TestGame
{
    class Entity
    {
    public:
        Entity() { m_Visible = true; m_Transform.Position = glm::vec3(0.0f); };
        ~Entity(){};
        virtual void OnLoad() {};
        virtual void OnUpdate(float dt, std::vector<Entity*> entities) {};
        virtual void OnDraw() {};
        virtual void OnUnload() {};
        virtual void Collide(Entity* entity) {};
        virtual void OnEvent(Rosewood::Event &e) {};
        virtual glm::vec3 GetPosition() {return m_Transform.Position;}
        virtual Rosewood::Ref<Rosewood::Sprite> GetSprite() {return m_Sprite;}
        virtual Rosewood::Rect GetBounds() { return m_Sprite->GetBounds(m_Transform); }
        virtual bool GetSolid() { return m_IsSolid; }


    protected:
        bool m_Visible;
        bool m_IsSolid = true;
        Rosewood::Ref<Rosewood::Sprite> m_Sprite;
        Rosewood::Transform m_Transform;
    };
}
