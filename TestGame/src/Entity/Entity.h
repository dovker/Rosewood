#pragma once
#include "Rosewood.h"
#include <glm/glm.hpp>


namespace TestGame
{
    class Entity
    {
    public:
        Entity() { m_Visible = true; m_Position = glm::vec3(0.0f); };
        ~Entity(){};
        virtual void OnLoad(Rosewood::AssetManager &assetManager) {};
        virtual void OnUpdate() {};
        virtual void OnDraw() {};
        virtual void OnUnload(Rosewood::AssetManager &assetManager) {};
        virtual void OnEvent(Rosewood::Event &e) {};
        virtual glm::vec3 GetPosition() {return m_Position;}


    private:
        bool m_Visible;
        glm::vec3 m_Position;
    };
}
