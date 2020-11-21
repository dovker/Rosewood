#pragma once
#include "Rosewood.h"
#include "Entity.h"
#include "Collision.h"
#include <glm/glm.hpp>


namespace TestGame
{
    class Player : public Entity
    {
    public:
        Player();
        void OnLoad(Rosewood::AssetManager &assetManager)   override;
        void OnUpdate() override;
        void OnDraw()   override;
        void OnUnload(Rosewood::AssetManager &assetManager) override;
        void OnEvent(Rosewood::Event &e) override;
        glm::vec3 GetPosition() override {return m_Position;}


    private:
        glm::vec3 m_Position;
        Rosewood::Ref<Rosewood::Texture> m_Texture;
        AABB collider;
    };
}
