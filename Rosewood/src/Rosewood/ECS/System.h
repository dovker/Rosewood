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
		virtual void OnRender2D() {}

        void AttachSceneData(Scene* scene) { m_Scene = scene; m_Registry = scene->GetRegistry(); }

    private:
        entt::registry* m_Registry; 
        Scene* m_Scene = nullptr;
    };
}