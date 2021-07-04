#include "rwpch.h"
#include "Scene.h"
#include "Components.h"
#include "Rosewood/Graphics/2D/Renderer2D.h"
#include "Rosewood/Core/Application.h"
#include "ScriptableEntity.h"
#include "Rosewood/Benchmark/Benchmark.h"
#include "Rosewood/Scripting/lua/LuaScript.h"


#include "Entity.h"

namespace Rosewood
{
	static std::mt19937 uidGenerator = std::mt19937(232345);
	static std::uniform_int_distribution<uint32_t> uidDistribution(0, std::numeric_limits<uint32_t>::max());

	bool Scene::ExistsUID(uint32_t uid)
	{
		bool val = false;
		auto view = m_Registry.view<UIDComponent>();
		for(auto entity : view)
		{
			val = view.get<UIDComponent>(entity).UID == uid;
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
		m_Registry.view<LuaScriptComponent>().each([=](auto entity, auto& scriptComponent)
		{
			scriptComponent.Script.OnDestroy();
		});
    }


    Entity Scene::CreateEntity(const std::string& name)
    {
        Entity entity = Entity(m_Registry.create(), this);
        entity.AddComponent<TransformComponent>();
		
        auto& tag = entity.AddComponent<TagComponent>();
        tag.Tag = name.empty() ? "Blank Entity" : name;

		auto& uidComponent = entity.AddComponent<UIDComponent>();
		uint32_t uid;
		do
		{
			uid = uidDistribution(uidGenerator);
		}
		while(ExistsUID(uid));
		uidComponent.UID = uid;

        return entity;
    }
    void Scene::DestroyEntity(Entity entity)
	{
		entity.GetComponent<LuaScriptComponent>().Script.OnDestroy();
		m_Registry.destroy(entity);
	}

    void Scene::OnUpdateRuntime(Timestep ts)
	{
        // Update scripts
		{
			m_Registry.view<LuaScriptComponent>().each([=](auto entity, auto& scriptComponent)
			{
				Rosewood::BenchmarkTimer timer = Rosewood::BenchmarkTimer("Lua OnUpdate");
				scriptComponent.Script.OnUpdate(ts);
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
		// Render 2D
		if (mainCamera)
		{
			Renderer2D::Begin(*mainCamera, cameraTransform);

			//Go Through sprites
			auto group = m_Registry.group<TransformComponent>(entt::get<SpriteRenderComponent>);
			for (auto entity : group)
			{
				if(m_Registry.has<LuaScriptComponent>(entity))
				{
					m_Registry.get<LuaScriptComponent>(entity).Script.OnRender2D();
				}
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
    Entity Scene::GetEntityByUID(uint32_t uid)
	{
		auto view = m_Registry.view<UIDComponent>();
		for (auto entity : view)
		{
			const auto& uidComp = view.get<UIDComponent>(entity);
			if (uidComp.UID == uid)
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
		component.Script.AttachScript(m_LuaState->GetPointer());
		component.Script.CallScript();
		component.Script.OnAttached(entity);
	}

	template<>
	void Scene::OnComponentAdded<TransformComponent>(Entity entity, TransformComponent& component)
	{
	}
	
	bool Scene::OnMouseButtonPressedEvent(Rosewood::MouseButtonPressedEvent& e)
	{
		m_Registry.view<LuaScriptComponent>().each([=](auto entity, auto& scriptComponent)
		{
			scriptComponent.Script.OnMouseButtonPressed(e.GetMouseButton());
		});
		return false;
	}
	bool Scene::OnMouseButtonReleasedEvent(Rosewood::MouseButtonReleasedEvent& e)
	{
		m_Registry.view<LuaScriptComponent>().each([=](auto entity, auto& scriptComponent)
		{
			scriptComponent.Script.OnMouseButtonReleased(e.GetMouseButton());
		});
		return false;
	}
	bool Scene::OnMouseMovedEvent(Rosewood::MouseMovedEvent& e)
	{
		m_Registry.view<LuaScriptComponent>().each([=](auto entity, auto& scriptComponent)
		{
			scriptComponent.Script.OnMouseMoved(e.GetX(), e.GetY());
		});
		return false;
	}
	bool Scene::OnMouseScrolledEvent(Rosewood::MouseScrolledEvent& e)
	{
		m_Registry.view<LuaScriptComponent>().each([=](auto entity, auto& scriptComponent)
		{
			scriptComponent.Script.OnMouseScrolled(e.GetXOffset(), e.GetYOffset());
		});
		return false;
	}
	bool Scene::OnKeyPressedEvent(Rosewood::KeyPressedEvent& e)
	{
		m_Registry.view<LuaScriptComponent>().each([=](auto entity, auto& scriptComponent)
		{
			scriptComponent.Script.OnKeyPressed(e.GetKeyCode());
		});
		return false;
	}
	bool Scene::OnKeyReleasedEvent(Rosewood::KeyReleasedEvent& e)
	{
		m_Registry.view<LuaScriptComponent>().each([=](auto entity, auto& scriptComponent)
		{
			scriptComponent.Script.OnKeyReleased(e.GetKeyCode());
		});
		return false;
	}
}