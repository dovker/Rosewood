#include "Scene.h"
#include "cmath"



namespace TestGame {
extern const uint32_t ChunkSize = 16;
extern const uint32_t ChunkArea = 256;
extern uint32_t TileSize = 8;

    Scene::Scene()
    {        
        
        m_Scene = Rosewood::Scene::Create();
    }

    void Scene::OnLoad()
    {
        Rosewood::SceneManager::SetScene(m_Scene);

        auto ent = m_Scene->CreateEntity("enity");
        ent.AddComponent<Rosewood::SpriteRenderComponent>("TempPlayer");

        auto childEnt = m_Scene->CreateEntity("enity2");
        childEnt.AddComponent<Rosewood::SpriteRenderComponent>("Sword");
        childEnt.GetComponent<Rosewood::TransformComponent>().TransformData.Position += glm::vec3(6.0f, 10.0f, 0.0f);

        ent.AddChild(childEnt);

        auto camera = m_Scene->CreateEntity("camera");
        camera.AddComponent<Rosewood::CameraComponent>();

        ent.AddComponent<Rosewood::LuaScriptComponent>("SampleScript", "SampleScript");
		camera.AddComponent<Rosewood::LuaScriptComponent>("CameraScript", "CameraScript");
        childEnt.AddComponent<Rosewood::LuaScriptComponent>("SwordScript", "SwordScript");

        //Rosewood::SceneManager::GetScene()->Serialize();
    }
    void Scene::OnUpdate(Rosewood::Timestep timestep)
    {
        Rosewood::SceneManager::OnUpdateRuntime(timestep);
        
    }
    void Scene::OnDraw()
    {
        {
            Rosewood::GraphicsCommand::SetClearColor(glm::vec4(0.1f, 0.12f, 0.1f, 1.0f));
            Rosewood::GraphicsCommand::Clear();
        }
        Rosewood::BatchRenderer::ResetStats();

        Rosewood::SceneManager::OnRenderRuntime();
        
    }
    void Scene::OnUnload()
    {
        for(auto& entity : m_Entities)
        {
            entity->OnUnload();
        }
    }
    void Scene::OnEvent(Rosewood::Event &e)
    {
        Rosewood::SceneManager::OnEvent(e);
        for(auto& entity : m_Entities)
        {
            entity->OnEvent(e);
        }
    }

    Map* Scene::GetMap() { return m_Map; }

}
