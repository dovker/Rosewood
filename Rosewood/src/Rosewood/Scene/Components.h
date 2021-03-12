#include "rwpch.h"
#include "Rosewood/Maths/Structs.h"
#include "Rosewood/Graphics/2D/Sprite.h"
#include "ScriptableEntity.h"

#include <glm/glm.hpp>


namespace Rosewood
{
    struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: Tag(tag) {}
	};

    struct TransformComponent
    {
        Transform Transform;

        TransformComponent() = default;
        TransformComponent(const TransformComponent&) = default;
        TransformComponent(const Transform transform)
            : Transform(transform) {}

        operator const Transform&() { return Transform; }
        glm::mat4 GetTransform() { return Transform.GetTransform(); }

    };

    struct SpriteRenderComponent
    {
        Ref<Sprite> Sprite;

        SpriteRenderComponent() = default;
        SpriteRenderComponent(const SpriteRenderComponent&) = default;
        SpriteRenderComponent(const Sprite sprite)
            : Sprite(sprite) {}

    };

    struct CameraComponent
    {
        SceneCamera Camera;
        bool Primary = true;
        bool FixedAspectRatio = false;

        CameraComponent() = default;
        CameraComponent(const CameraComponent&) = default;

        void Reset()
        {
            Primary = true;
            FixedAspectRatio = false;
        }
    };
    
    struct NativeScriptComponent
	{
		ScriptableEntity* Instance = nullptr;

		ScriptableEntity*(*InstantiateScript)();
		void (*DestroyScript)(NativeScriptComponent*);

		template<typename T>
		void Bind()
		{
			InstantiateScript = []() { return static_cast<ScriptableEntity*>(new T()); };
			DestroyScript = [](NativeScriptComponent* nsc) { delete nsc->Instance; nsc->Instance = nullptr; };
		}
	};
}