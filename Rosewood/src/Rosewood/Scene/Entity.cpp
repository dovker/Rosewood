#include "rwpch.h"
#include "Entity.h"

namespace Rosewood {

	Entity::Entity(entt::entity handle, Scene* scene)
		: m_EntityHandle(handle), m_Scene(scene)
	{
	}

}