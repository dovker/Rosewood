#include "Scene.h"
#include "cmath"

namespace TestGame {
extern const uint32_t ChunkSize = 16;
extern const uint32_t ChunkArea = 256;
extern uint32_t TileSize = 8;

    Scene::Scene()
    {        
        
        m_Scene = Rosewood::CreateRef<Rosewood::Scene>();
    }

    void Scene::OnLoad()
    {
        Rosewood::Ref<Rosewood::Texture> mapTexture = Rosewood::AssetManager::Load<Rosewood::Texture>("Tileset.png", "Tileset");
       
        Rosewood::Ref<Rosewood::Sprite> sprite = Rosewood::Sprite::Create(mapTexture);

        auto ent = m_Scene->CreateEntity("enity");
        ent.AddComponent<Rosewood::SpriteRenderComponent>(sprite);

        auto camera = m_Scene->CreateEntity("camera");
        camera.AddComponent<Rosewood::CameraComponent>();

        class CameraController : public Rosewood::ScriptableEntity
		{
		public:
			virtual void OnCreate() override
			{
                Rosewood::Transform& translation = GetComponent<Rosewood::TransformComponent>();
                //translation.Position.z = -.3f;
			}

			virtual void OnDestroy() override
			{
			}

			virtual void OnUpdate(Rosewood::Timestep ts) override
			{
				Rosewood::Transform& translation = GetComponent<Rosewood::TransformComponent>();

				float speed = 5.0f;

				if (Rosewood::Input::IsKeyPressed(KEY_A)) //switch to key::a
					translation.Position.x -= speed * ts;
				if (Rosewood::Input::IsKeyPressed(KEY_D))
					translation.Position.x += speed * ts;
				if (Rosewood::Input::IsKeyPressed(KEY_W))
					translation.Position.y -= speed * ts;
				if (Rosewood::Input::IsKeyPressed(KEY_S))
					translation.Position.y += speed * ts;

                //RW_INFO("{0}, {1}, {2}", translation.Position.x, translation.Position.y, translation.Position.z);
			}
		};

		camera.AddComponent<Rosewood::NativeScriptComponent>().Bind<CameraController>();
    }
    void Scene::OnUpdate(Rosewood::Timestep timestep)
    {
        m_Scene->OnUpdateRuntime(timestep);
        
    }
    void Scene::OnDraw()
    {
        {
            Rosewood::GraphicsCommand::SetClearColor(glm::vec4(0.1f, 0.12f, 0.1f, 1.0f));
            Rosewood::GraphicsCommand::Clear();
        }
        Rosewood::BatchRenderer::ResetStats();

        m_Scene->OnRenderRuntime();
        
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
        m_Scene->OnEvent(e);
        for(auto& entity : m_Entities)
        {
            entity->OnEvent(e);
        }
    }

    Map* Scene::GetMap() { return m_Map; }

}
