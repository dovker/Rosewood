#include "Scene.h"
#include "cmath"

namespace TestGame {
extern const uint32_t ChunkSize = 16;
extern const uint32_t ChunkArea = 256;
extern uint32_t TileSize = 16;

    Scene::Scene()
    {        
        m_Camera = new Camera(glm::vec2(Rosewood::Application::Get().GetWindow().GetWidth() / 4, Rosewood::Application::Get().GetWindow().GetHeight() / 4));
        
        Entity* m_Player = new Player();
        m_Entities = std::vector<Entity*>
        {
            m_Player,
        };
        m_Camera->SetTarget(m_Player);
        
        m_Map = new Map(100, 100);
        
        for (int i = 0; i<100; i++)
        {
            for (int j = 0; j<100; j++)
            {
                m_Map->Set(i, j, 17); //TODO: TEST THIS
            }
        }
        
        Rosewood::BatchRenderer::Init();
    }
    void Scene::OnLoad()
    {
        for(auto& entity : m_Entities)
        {
            entity->OnLoad();
        }
        Rosewood::Ref<Rosewood::Texture> mapTexture = Rosewood::AssetManager::Load<Rosewood::Texture>("Content/Tileset.png", "Tileset");
        m_Map->SetTexture(mapTexture);
    }
    void Scene::OnUpdate(Rosewood::Timestep timestep)
    {
        m_Camera->OnUpdate(timestep);
        for(auto& entity : m_Entities)
        {
            entity->OnUpdate(timestep, m_Entities);

        }
    }
    void Scene::OnDraw()
    {
        {
            Rosewood::GraphicsCommand::SetClearColor(glm::vec4(0.1f, 0.12f, 0.1f, 1.0f));
            Rosewood::GraphicsCommand::Clear();
        }
        Rosewood::BatchRenderer::ResetStats();

        
        Rosewood::Renderer2D::Begin(m_Camera->GetCamera());
        
        m_Map->Draw();
        
        for(auto& entity : m_Entities)
        {
            entity->OnDraw();
        }
        
        Rosewood::Renderer2D::End();
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
        m_Camera->OnEvent(e);
        for(auto& entity : m_Entities)
        {
            entity->OnEvent(e);
        }
    }

}
