#include "Scene.h"
#include "cmath"

namespace TestGame {
extern const uint32_t ChunkSize = 16;
extern const uint32_t ChunkArea = 256;
extern uint32_t TileSize = 16;

    Scene::Scene()
    {        
        
        m_Camera = new Camera(glm::vec2(Rosewood::Application::Get().GetWindow().GetWidth() / 4, Rosewood::Application::Get().GetWindow().GetHeight() / 4));
        
        m_Entities = std::vector<Entity*>
        {
            new Player(),
        };
        m_Map = new Map(100, 100);
        
        for (int i = 0; i<100; i++)
        {
            for (int j = 0; j<100; j++)
            {
                m_Map->Set(i, j, 17); //TODO: TEST THIS
            }
        }
        RW_TRACE("{0}", m_Map->Get(31, 31));
        
        Rosewood::BatchRenderer::Init();
    }
    void Scene::OnLoad(Rosewood::AssetManager &assetManager)
    {
        for(auto& entity : m_Entities)
        {
            entity->OnLoad(assetManager);
        }
        Rosewood::Ref<Rosewood::Texture> mapTexture = assetManager.Load<Rosewood::Texture>("Content/Tileset.png", "Tileset");
        m_Map->SetTexture(mapTexture);
    }
    void Scene::OnUpdate()
    {
        for(auto& entity : m_Entities)
        {
            entity->OnUpdate();
            
            float xPos = glm::mix(m_Camera->GetCamera().GetPosition().x, entity->GetPosition().x - 1280.0f/2/4 + 8, 0.1);
            float yPos = glm::mix(m_Camera->GetCamera().GetPosition().y, entity->GetPosition().y - 720.0f/2/4 + 8, 0.1);
            
            m_Camera->SetPosition(glm::vec3(xPos, yPos, 0.0f));

        }
    }
    void Scene::OnDraw()
    {
        {
            Rosewood::GraphicsCommand::SetClearColor(glm::vec4(0.1f, 0.12f, 0.1f, 1.0f));
            Rosewood::GraphicsCommand::Clear();
        }
        Rosewood::BatchRenderer::ResetStats();

        
        Rosewood::BatchRenderer::Begin(m_Camera->GetCamera());
        
        m_Map->Draw();
        
        for(auto& entity : m_Entities)
        {
            entity->OnDraw();
        }
        
        Rosewood::BatchRenderer::End();
    }
    void Scene::OnUnload(Rosewood::AssetManager &assetManager)
    {
        for(auto& entity : m_Entities)
        {
            entity->OnUnload(assetManager);
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
