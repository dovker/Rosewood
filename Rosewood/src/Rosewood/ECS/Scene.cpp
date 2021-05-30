#include "rwpch.h"
#include "Scene.h"
#include "Components.h"
#include "Rosewood/Graphics/2D/Renderer2D.h"
#include "Rosewood/Core/Application.h"


#include "Entity.h"
#include "System.h"

namespace Rosewood
{
    Scene::Scene()
    {
		m_ViewportWidth = Rosewood::Application::Get().GetWindow().GetWidth();
		m_ViewportHeight = Rosewood::Application::Get().GetWindow().GetHeight();
    }
    Scene::~Scene()
    {
    }

	void Scene::AddSystem(System& system)
	{
		m_Systems.push_back(system);
		system.OnAttached();
		system.AttachSceneData(this);
	}

    Entity Scene::CreateEntity(const std::string& name)
    {
        Entity entity = Entity(m_Registry.create(), this);
        entity.AddComponent<TransformComponent>();
        auto& tag = entity.AddComponent<TagComponent>();
        tag.Tag = name.empty() ? "Blank Entity" : name;
        return entity;
    }
    void Scene::DestroyEntity(Entity entity)
	{
		m_Registry.destroy(entity);
	}

    void Scene::OnUpdateRuntime(Timestep ts)
	{
        //Go through systems
		{
			for(auto& sys : m_Systems)
			{
				sys.OnUpdate(ts);
			}
		}

        // Update scripts
		{
			m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
			{
				// TODO: Move to Scene::OnScenePlay
				if (!nsc.Instance)
				{
					nsc.Instance = nsc.InstantiateScript();
					nsc.Instance->m_Entity = Entity{ entity, this };
					nsc.Instance->OnCreate();
				}

				nsc.Instance->OnUpdate(ts);
			});
		}

		
    }

	void Scene::OnRenderRuntime()
	{
		Camera* mainCamera = nullptr;
		glm::mat4 cameraTransform;
		{
			auto view = m_Registry.view<TransformComponent, CameraComponent>();
			for (auto entity : view)
			{
				auto [transform, camera] = view.get<TransformComponent, CameraComponent>(entity);
				
				if (camera.Primary)
				{
					mainCamera = &camera.Camera;
					cameraTransform = transform.GetTransform();
					break;
				}
			}
		}
		//Go through systems
		{
			for(auto& sys : m_Systems)
			{
				sys.OnRender();
			}
		}
		// Render 2D
		if (mainCamera)
		{
			Renderer2D::Begin(*mainCamera, cameraTransform);

			//Go through systems
			{
				for(auto& sys : m_Systems)
				{
					sys.OnRender2D();
				}
			}

			//Go Through sprites
			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRenderComponent>);
			for (auto entity : group)
			{
				auto [transform, sprite] = group.get<TransformComponent, SpriteRenderComponent>(entity);
                Renderer2D::Draw(sprite.GetSprite(), transform);
			}

			//Go Through Scripts
			{
				m_Registry.view<NativeScriptComponent>().each([=](auto entity, auto& nsc)
				{
					nsc.Instance->OnRender2D();
				});
			}

			Renderer2D::End();
		}
	}

    Entity Scene::GetPrimaryCameraEntity()
	{
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			const auto& camera = view.get<CameraComponent>(entity);
			if (camera.Primary)
				return Entity{entity, this};
		}
		return {};
	}

	void Scene::OnEvent(Event& e)
	{
		Rosewood::EventDispatcher dispatcher(e);
        dispatcher.Dispatch<Rosewood::WindowResizeEvent>(RW_BIND_EVENT_FN(Scene::OnViewportResize));
	}
    bool Scene::OnViewportResize(Rosewood::WindowResizeEvent& e)
	{
		m_ViewportWidth = e.GetWidth();
		m_ViewportHeight = e.GetHeight();
		#ifdef RW_PLATFORM_MACOS
        m_ViewportWidth *= 0.5f;
		m_ViewportHeight *= 0.5f;
        #endif

		// Resize our non-FixedAspectRatio cameras
		auto view = m_Registry.view<CameraComponent>();
		for (auto entity : view)
		{
			auto& cameraComponent = view.get<CameraComponent>(entity);
			if (!cameraComponent.FixedAspectRatio)
				cameraComponent.Camera.SetViewportSize(m_ViewportWidth, m_ViewportHeight);
		}
		return false;
	}

    template<typename T>
	void Scene::OnComponentAdded(Entity entity, T& component)
	{
		//static_assert(false);
	}

    template<>
	void Scene::OnComponentAdded<CameraComponent>(Entity entity, CameraComponent& component)
	{
		if (m_ViewportWidth > 0 && m_ViewportHeight > 0)
			component.Camera.SetViewportSize(m_ViewportWidth, m_ViewportHeight);
	}
	template<>
	void Scene::OnComponentAdded<SpriteRenderComponent>(Entity entity, SpriteRenderComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<TagComponent>(Entity entity, TagComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<NativeScriptComponent>(Entity entity, NativeScriptComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& component)
	{
	}

}