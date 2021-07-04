#include "rwpch.h"

#include "SceneManager.h"
#include "Rosewood/Scripting/lua/LuaState.h"

namespace Rosewood
{
    struct SceneData
    {
        Ref<Scene> Scene;
        std::vector<System> Systems;
    };
    static SceneData s_Data;

    Ref<Scene> SceneManager::GetScene() { return s_Data.Scene; }
    void SceneManager::SetScene(Ref<Scene> scene)
    {
        s_Data.Scene = scene;
        for(auto& system : s_Data.Systems)
        {
            system.AttachSceneData(scene);
        }
    }
    void SceneManager::LoadScene(const std::string& name)
    {
        //.... AFTER SERIALIZATION
        //SetScene(ref);
    }

    void SceneManager::AddSystem(System& system)
    {
		s_Data.Systems.push_back(system);
		system.OnAttached();
    }

    void SceneManager::OnUpdateRuntime(Timestep ts)
    {
        //Go through systems
		{
			for(auto& sys : s_Data.Systems)
			{
				sys.OnUpdate(ts);
			}
		}

        s_Data.Scene->OnUpdateRuntime(ts);
    }
    void SceneManager::OnRenderRuntime()
    {
		//Go through systems
		{
			for(auto& sys : s_Data.Systems)
			{
				sys.OnRender();
			}
		}
        s_Data.Scene->OnRenderRuntime();
    }
    void SceneManager::OnEvent(Event& e)
    {
        s_Data.Scene->OnEvent(e);
    }
}