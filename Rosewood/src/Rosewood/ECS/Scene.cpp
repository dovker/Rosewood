#include "rwpch.h"
#include "Scene.h"
#include "Components.h"
#include "Rosewood/Graphics/2D/Renderer2D.h"
#include "Rosewood/Core/Application.h"
#include "ScriptableEntity.h"
#include "Rosewood/Benchmark/Benchmark.h"

#include "Entity.h"

namespace Rosewood
{
	static std::mt19937 uuidGenerator = std::mt19937(232345);
	static std::uniform_int_distribution<uint64_t> uuidDistribution(0, std::numeric_limits<uint64_t>::max());

	bool Scene::ExistsUUID(uint64_t uuid)
	{
		bool val = false;
		auto view = m_Registry.view<UUIDComponent>();
		for(auto entity : view)
		{
			val = view.get<UUIDComponent>(entity).UUID == uuid;
			if(val) break;
		}
		return val;
	}

    Scene::Scene()
    {
		m_ViewportWidth = Rosewood::Application::Get().GetWindow().GetWidth();
		m_ViewportHeight = Rosewood::Application::Get().GetWindow().GetHeight();
		m_LuaState = LuaState::Create();
    }
    Scene::~Scene()
    {
		m_LuaState->DestroyScripts();
    }


    Entity Scene::CreateEntity(const std::string& name)
    {
		uint64_t uuid;
		do
		{
			uuid = uuidDistribution(uuidGenerator);
		}
		while(ExistsUUID(uuid) && uuid != 0);
        return CreateEntity(name, uuid);
    }
	Entity Scene::CreateEntity(const std::string& name, uint64_t uuid)
	{
		Entity entity = Entity(m_Registry.create(), this);
        entity.AddComponent<TransformComponent>();
		
        auto& tag = entity.AddComponent<TagComponent>();
        tag.Tag = name.empty() ? "Blank Entity" : name;

		entity.AddComponent<UUIDComponent>(uuid);

		return entity;
	}
    void Scene::DestroyEntity(Entity entity)
	{
		m_LuaState->UnregisterScript(entity);
		m_Registry.destroy(entity);
	}

    void Scene::OnUpdateRuntime(Timestep ts)
	{
		BenchmarkTimer timer("Updating");
        // Update scripts
		{
			m_LuaState->CallOnUpdate(ts);
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
		// Render 2D
		if (mainCamera)
		{
			BenchmarkTimer timer("2D Rendering");
			Renderer2D::Begin(*mainCamera, cameraTransform);

			m_LuaState->CallVoidScriptFunction("OnRender2D");
			//Go Through sprites
			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRenderComponent>);
			for (auto entity : group)
			{
				auto [transform, sprite] = group.get<TransformComponent, SpriteRenderComponent>(entity);
				Transform t;
				
				if(m_Registry.has<RelationshipComponent>(entity))
				{
					t = transform.GetHierarchy(entity, m_Registry);
				}
				else
					t = transform;
				
				Renderer2D::Draw(sprite.GetSprite(), t); //MAY BE INEFFICIENT
				
				
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
    Entity Scene::GetEntityByID(uint32_t id)
	{
		return Entity{(entt::entity)id, this};
	}
    Entity Scene::GetEntityByUUID(uint64_t uuid)
	{
		auto view = m_Registry.view<UUIDComponent>();
		for (auto entity : view)
		{
			const auto& uuidComp = view.get<UUIDComponent>(entity);
			if (uuidComp.UUID == uuid)
				return Entity{entity, this};
		}
		return {};
	}

	void Scene::OnEvent(Event& e)
	{
		Rosewood::EventDispatcher dispatcher(e);
        dispatcher.Dispatch<Rosewood::WindowResizeEvent>(RW_BIND_EVENT_FN(Scene::OnViewportResize));
		dispatcher.Dispatch<Rosewood::MouseButtonPressedEvent>(RW_BIND_EVENT_FN(Scene::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<Rosewood::MouseButtonReleasedEvent>(RW_BIND_EVENT_FN(Scene::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<Rosewood::MouseMovedEvent>(RW_BIND_EVENT_FN(Scene::OnMouseMovedEvent));
		dispatcher.Dispatch<Rosewood::MouseScrolledEvent>(RW_BIND_EVENT_FN(Scene::OnMouseScrolledEvent));
		dispatcher.Dispatch<Rosewood::KeyPressedEvent>(RW_BIND_EVENT_FN(Scene::OnKeyPressedEvent));
		dispatcher.Dispatch<Rosewood::KeyReleasedEvent>(RW_BIND_EVENT_FN(Scene::OnKeyReleasedEvent));
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
	void Scene::OnComponentAdded<RelationshipComponent>(Entity entity, RelationshipComponent& component)
	{
	}


	template<>
	void Scene::OnComponentAdded<TagComponent>(Entity entity, TagComponent& component)
	{
	}

	template<>
	void Scene::OnComponentAdded<LuaScriptComponent>(Entity entity, LuaScriptComponent& component)
	{
		m_LuaState->CallScript(component.Script);
		m_LuaState->RegisterScript(entity, component.TableName);
		m_LuaState->CallVoidIndividualFunction(entity, "OnCreate");
	}

	template<>
	void Scene::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& component)
	{
	}
	
	bool Scene::OnMouseButtonPressedEvent(Rosewood::MouseButtonPressedEvent& e)
	{
		m_LuaState->CallOnMouseButtonPressed(e.GetMouseButton());
		return false;
	}
	bool Scene::OnMouseButtonReleasedEvent(Rosewood::MouseButtonReleasedEvent& e)
	{
		m_LuaState->CallOnMouseButtonReleased(e.GetMouseButton());
		return false;
	}
	bool Scene::OnMouseMovedEvent(Rosewood::MouseMovedEvent& e)
	{
		m_LuaState->CallOnMouseMoved(e.GetX(), e.GetY());
		return false;
	}
	bool Scene::OnMouseScrolledEvent(Rosewood::MouseScrolledEvent& e)
	{
		m_LuaState->CallOnMouseScrolled(e.GetXOffset(), e.GetYOffset());
		return false;
	}
	bool Scene::OnKeyPressedEvent(Rosewood::KeyPressedEvent& e)
	{
		m_LuaState->CallOnKeyPressed(e.GetKeyCode());
		return false;
	}
	bool Scene::OnKeyReleasedEvent(Rosewood::KeyReleasedEvent& e)
	{
		m_LuaState->CallOnKeyReleased(e.GetKeyCode());
		return false;
	}
}
