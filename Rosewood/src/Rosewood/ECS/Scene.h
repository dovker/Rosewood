#pragma once
#include "Rosewood/Core/Timestep.h"
#include "Rosewood/Events/Event.h"
#include "Rosewood/Events/MouseEvent.h"
#include "Rosewood/Events/KeyEvent.h"
#include "Rosewood/Events/ApplicationEvent.h"
#include "entt.hpp"
#include "Rosewood/Scripting/lua/LuaState.h"
#include "Rosewood/Files/File.h"

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
        Entity CreateEntity(const std::string& name, uint64_t uuid);
		void DestroyEntity(Entity entity);

		void OnUpdateRuntime(Timestep ts);
        void OnRenderRuntime();
        bool OnViewportResize(Rosewood::WindowResizeEvent& e);

        bool OnMouseButtonPressedEvent(Rosewood::MouseButtonPressedEvent& e);
        bool OnMouseButtonReleasedEvent(Rosewood::MouseButtonReleasedEvent& e);
        bool OnMouseMovedEvent(Rosewood::MouseMovedEvent& e);
        bool OnMouseScrolledEvent(Rosewood::MouseScrolledEvent& e);
        bool OnKeyPressedEvent(Rosewood::KeyPressedEvent& e);
        bool OnKeyReleasedEvent(Rosewood::KeyReleasedEvent& e);

        void OnEvent(Event& e);

        //GetEntity(const std::string& name);

        Entity GetPrimaryCameraEntity();
        Entity GetEntityByID(uint32_t id);
        Entity GetEntityByUUID(uint64_t uuid);
        entt::registry* GetRegistry() { return &m_Registry; }

        static Ref<Scene> Create()
        {
            return CreateRef<Scene>();
        }

    private:
        template<typename T>
		void OnComponentAdded(Entity entity, T& component);
        bool ExistsUUID(uint64_t uuid);

        uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
        entt::registry m_Registry; 
        Ref<LuaState> m_LuaState;


        friend class Entity;
        friend class System;
    };

}