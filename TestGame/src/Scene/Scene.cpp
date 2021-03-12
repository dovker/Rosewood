#include "Scene.h"
#include "cmath"

namespace TestGame {
extern const uint32_t ChunkSize = 16;
extern const uint32_t ChunkArea = 256;
extern uint32_t TileSize = 8;

    Scene::Scene()
    {        
        m_Camera = new GameCamera(glm::vec2(Rosewood::Application::Get().GetWindow().GetWidth(), Rosewood::Application::Get().GetWindow().GetHeight()));
        
        m_Map = new Map(1000, 1000);
        
        for (int j = 0; j<1000; j++)
        {
            for (int i = 0; i<1000; i++)
            {
                glm::vec2 st(i, j);
                float value = glm::abs(Rosewood::Noise::FBM(st / 50.832f * 2.0f, 3, 0.5f, 54534.532f) - 0.5f) * 2.0f;
                if(value > 0.15f)
                {
                    m_Map->Set(i, j, SET_TEX_INDEX(1) | TILE_ISBLOCK); 
                }
                else{
                    m_Map->Set(i, j, 0); 
                }
            }
        }
        
        Entity* m_Player = new Player();
        m_Entities = std::vector<Entity*>
        {
            m_Player,
        };
        m_Camera->SetTarget(m_Player);
    }
    void Scene::OnLoad()
    {
        Rosewood::Ref<Rosewood::Texture> mapTexture = Rosewood::AssetManager::Load<Rosewood::Texture>("Content/Tileset.png", "Tileset");
        m_Map->SetTexture(mapTexture);
    
        for(auto& entity : m_Entities)
        {
            entity->OnLoad();
        }
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
        
        m_Map->Draw(m_Camera);
        
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

    Map* Scene::GetMap() { return m_Map; }

}
