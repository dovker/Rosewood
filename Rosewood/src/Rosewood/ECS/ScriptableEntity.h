#pragma once

#include "Entity.h"

namespace Rosewood {

	class ScriptableEntity
	{
	public:
		virtual ~ScriptableEntity() {}

		template<typename T>
		T& GetComponent()
		{
			return m_Entity.GetComponent<T>();
		}
		Entity GetSelf() 
		{
			return m_Entity;
		}
	protected:
		virtual void OnCreate() {}
		virtual void OnDestroy() {}
		virtual void OnUpdate(Timestep ts) {}
		virtual void OnRender2D() {}
	private:
		friend class Scene;
		friend class Entity;

		Entity m_Entity;
		
	};

}