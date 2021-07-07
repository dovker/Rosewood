#pragma once
#include "rwpch.h"
#include "Rosewood/Maths/Structs.h"
#include "Rosewood/Graphics/2D/Sprite.h"

#include <glm/glm.hpp>
#include "SceneCamera.h"
#include "entt.hpp"

#include "Rosewood/Scripting/lua/LuaScript.h"

namespace Rosewood
{
    struct UUIDComponent
	{
		uint64_t UUID;

		UUIDComponent() = default;
		UUIDComponent(const UUIDComponent&) = default;
		UUIDComponent(uint64_t uuid)
			: UUID(uuid) {}
	};
    struct TagComponent
	{
		std::string Tag;

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(const std::string& tag)
			: Tag(tag) {}
	};
    struct RelationshipComponent
	{
		std::size_t Children{0};
        entt::entity First{entt::null};
        entt::entity Prev{entt::null};
        entt::entity Next{entt::null};
        entt::entity Parent{entt::null};

		RelationshipComponent() = default;
		RelationshipComponent(const RelationshipComponent&) = default;
		RelationshipComponent(entt::entity parent)
			: Parent(parent) {}
	};

    struct TransformComponent
    {
        Transform TransformData;

        TransformComponent() = default;
        TransformComponent(const TransformComponent&) = default;
        TransformComponent(const Transform transform)
            : TransformData(transform) {}

        operator Transform&() { return TransformData; }
        glm::mat4 GetTransform() { return TransformData.GetTransform(); }
        Transform GetHierarchy(entt::entity handle, const entt::registry& reg) const
        {
			if(reg.has<RelationshipComponent>(handle))
			{
                entt::entity parent = reg.get<RelationshipComponent>(handle).Parent;
                if(parent != entt::null && reg.has<TransformComponent>(parent))
                {
				    auto& trans = reg.get<TransformComponent>(parent);
                    return TransformData + trans.GetHierarchy(parent, reg);
                }
			}
            return TransformData;
        }
        glm::mat4 GetHierarchyTransform(entt::entity handle, const entt::registry& reg) const
        { 
            return GetHierarchy(handle, reg).GetTransform(); 
        }
    };

    struct SpriteRenderComponent
    {
        Sprite SpriteData;
        std::string AssetName;

        SpriteRenderComponent() = default;
        SpriteRenderComponent(const SpriteRenderComponent&) = default;

        SpriteRenderComponent(const std::string& assetName)
            : AssetName(assetName), SpriteData(assetName){}

        void ChangeAsset(const std::string& assetName)
        {
            AssetName = assetName;
            SpriteData.ReloadTexture(assetName);
        }

        Sprite& GetSprite() { return SpriteData; }
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

    struct LuaScriptComponent
	{
		LuaScript Script;
        std::string AssetName;

        LuaScriptComponent() = default;
        LuaScriptComponent(const LuaScriptComponent&) = default;
        LuaScriptComponent(const LuaScript& luaScript, const std::string& assetName)
            : Script(luaScript), AssetName(assetName) {}
        LuaScriptComponent(const std::string& assetName, const std::string& tableName)
            : AssetName(assetName), Script(assetName, tableName)
        { }
	};
}