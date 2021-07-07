#include "rwpch.h"

#include "SceneManager.h"
#include "Rosewood/Assets/AssetManager.h"
#include "Rosewood/Files/File.h"
#include "Rosewood/Data/SceneSerializer.h"

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
        auto scene = Scene::Create();
        std::string data;
		SceneSerializer s(scene);
		s.Deserialize(AssetManager::Get<TextFile>(name)->GetData());
        SetScene(scene);
    }
    void SceneManager::SaveScene(const std::string& filepath)
    {
		SceneSerializer s(s_Data.Scene);
		try
        {
            std::ofstream ofs(filepath);
            ofs.exceptions(std::ofstream::badbit | std::ofstream::failbit);
            ofs << s.Serialize();
            if(ofs.bad())
			{
				throw std::invalid_argument("Error Reading the file");
			}
		}
		catch (const std::invalid_argument& e)
		{
            RW_CORE_ERROR("SCENE OFSTREAM ERROR: {0}", e.what());
        }
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