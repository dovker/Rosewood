#pragma once

#include "Scene.h"
#include "entt.hpp"
#include "Components.h"

namespace Rosewood
{
    class Entity
	{
	public:
		Entity() = default;
		Entity(entt::entity handle, Scene* scene);
		Entity(const Entity& other) = default;

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			RW_CORE_ASSERT(!HasComponent<T>(), "Entity already has component!");
			T& component = m_Scene->m_Registry.emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
			m_Scene->OnComponentAdded<T>(*this, component);
			return component;
		}

		template<typename T>
		T& GetComponent() const
		{
			RW_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			return m_Scene->m_Registry.get<T>(m_EntityHandle);
		}

		template<typename T>
		bool HasComponent() const
		{
			return m_Scene->m_Registry.has<T>(m_EntityHandle);
		}

		template<typename T>
		void RemoveComponent()
		{
			RW_CORE_ASSERT(HasComponent<T>(), "Entity does not have component!");
			m_Scene->m_Registry.remove<T>(m_EntityHandle);
		}

		void AddChild(Entity& child)
		{
			if(!HasComponent<RelationshipComponent>())
			{
				AddComponent<RelationshipComponent>();
			}
			if(!child.HasComponent<RelationshipComponent>())
			{
				child.AddComponent<RelationshipComponent>();
			}
			auto &relation = GetComponent<RelationshipComponent>();
			auto &childRelation = GetComponent<RelationshipComponent>();
			child.GetComponent<RelationshipComponent>().Parent = m_EntityHandle;
			if(relation.First != entt::null)
			{
				auto &tempRelation = m_Scene->m_Registry.get<RelationshipComponent>(relation.First);
				if(tempRelation.Next != entt::null)
					childRelation.Next = tempRelation.Next;

				tempRelation.Next = child;
				childRelation.Prev = relation.First;
			}
			else
			{
				relation.First = child;
			}
			relation.Children++;
		}
		std::vector<entt::entity> GetChildren() //TODO: TEST
		{
			if(HasComponent<RelationshipComponent>())
			{
				auto &relation = GetComponent<RelationshipComponent>();
				auto curr = relation.First;
				std::vector<entt::entity> vector(relation.Children);

				for(std::size_t i{}; i < relation.Children; ++i) {
					curr = m_Scene->m_Registry.get<RelationshipComponent>(curr).Next;
				}
			}
			return {};
		}
		entt::entity GetChild(const std::string& tagName) const //TODO: TEST
		{
			if(HasComponent<RelationshipComponent>())
			{
				auto &relation = GetComponent<RelationshipComponent>();
				auto curr = relation.First;
				std::vector<entt::entity> vector(relation.Children);

				for(std::size_t i{}; i < relation.Children; ++i) {
					if(m_Scene->m_Registry.get<TagComponent>(curr).Tag == tagName)
						return curr;
					curr = m_Scene->m_Registry.get<RelationshipComponent>(curr).Next;
				}
			}
			return entt::null;
		}
		Entity GetChildEntity(const std::string& tagName) const
		{
			return Entity(GetChild(tagName), m_Scene);
		}
		Scene* GetScene() { return m_Scene; }

		operator bool() const { return m_EntityHandle != entt::null; }
		operator entt::entity() const { return m_EntityHandle; }
		operator uint32_t() const { return (uint32_t)m_EntityHandle; }

		bool operator==(const Entity& other) const
		{
			return m_EntityHandle == other.m_EntityHandle && m_Scene == other.m_Scene;
		}

		bool operator!=(const Entity& other) const
		{
			return !(*this == other);
		}
	private:
		entt::entity m_EntityHandle{ entt::null };
		Scene* m_Scene = nullptr;
	};


}