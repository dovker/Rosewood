#pragma once
#include "Rosewood/Core/Timestep.h"
#include "Rosewood/Events/Event.h"
#include "Rosewood/Events/ApplicationEvent.h"
#include "entt.hpp"

namespace Rosewood
{
    class Entity;
    class System;

    class Scene
    {
    public:
        Scene();
        ~Scene();

        Entity CreateEntity(const std::string& name = std::string());
		void DestroyEntity(Entity entity);

		void OnUpdateRuntime(Timestep ts);
        void OnRenderRuntime();
        bool OnViewportResize(Rosewood::WindowResizeEvent& e);
        void OnEvent(Event& e);

        void AddSystem(System& system);

        Entity GetPrimaryCameraEntity();
        entt::registry* GetRegistry() { return &m_Registry; }

    private:
        template<typename T>
		void OnComponentAdded(Entity entity, T& component);

        uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
        entt::registry m_Registry; 

        std::vector<System> m_Systems;

        friend class Entity;
        friend class System;
    };
}