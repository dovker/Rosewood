#pragma once
#include "Scene.h"
#include "System.h"


namespace Rosewood
{
    class SceneManager
    {
    public:
        static Ref<Scene> GetScene();
        static void SetScene(Ref<Scene> scene);
        //TODO FINISH
        static void LoadScene(const std::string& name);

        void AddSystem(System& system);

        static void OnUpdateRuntime(Timestep ts);
        static void OnRenderRuntime();
        static void OnEvent(Event& e);
        
    };
}