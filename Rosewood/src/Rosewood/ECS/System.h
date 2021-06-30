#pragma once

#include "Scene.h"

#include "entt.hpp"
#include "Rosewood/Core/Timestep.h"



namespace Rosewood
{
    class System //Add Tags, names of some sorts for benchmarking
    {
    public:
        
        System() {};
        ~System() {};
        virtual void OnAttached() {}

		virtual void OnUpdate(Timestep ts) {}

        virtual void OnRender() {}

        void AttachSceneData(Ref<Scene> scene) { m_Scene = scene; m_Registry = scene->GetRegistry(); }

    private:
        entt::registry* m_Registry; 
        Ref<Scene> m_Scene = nullptr;
    };
}