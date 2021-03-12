#pragma once
#include "Rosewood/Core/Timestep.h"
#include "entt.hpp"

namespace Rosewood
{
    class Entity;

    class Scene
    {
    public:
        Scene();
        ~Scene();

        Entity CreateEntity(const std::string& name = std::string());
		void DestroyEntity(Entity entity);

		void OnUpdateRuntime(Timestep ts);
        void OnViewportResize(uint32_t width, uint32_t height);

        Entity GetPrimaryCameraEntity();

    private:
        template<typename T>
		void OnComponentAdded(Entity entity, T& component);

        uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
        entt::registry m_Registry; 

        friend class Entity;
    };
}