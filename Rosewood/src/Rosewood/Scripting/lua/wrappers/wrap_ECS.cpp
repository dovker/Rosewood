#include "rwpch.h"

#include "wrap_ECS.h"

#include "Rosewood/ECS/SceneManager.h"
#include "Rosewood/ECS/Scene.h"
#include "Rosewood/ECS/Entity.h"
#include "Rosewood/ECS/SceneManager.h"

#include "Rosewood/Maths/Structs.h"

#include "Rosewood/Graphics/2D/Sprite.h"


extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

#include "sol/sol.hpp"

namespace Rosewood
{
    const char* wrap_ECS::Name = "ECS";

    wrap_ECS::wrap_ECS(lua_State* L)
    {
        sol::state_view lua(L);
        lua.new_usertype<Animation2D>("Animation2D",
            "Speed", &Animation2D::Speed,
            "Frame", &Animation2D::Frame,
            "TotalFrames", &Animation2D::TotalFrames,
            "Playing", &Animation2D::Playing,
            "Loops", &Animation2D::Loops
        );
        lua.new_usertype<Offset2D>("Offset2D",
            "Pivot", &Offset2D::Pivot,
            "FlippedX", &Offset2D::FlippedX,
            "FlippedY", &Offset2D::FlippedY
        );

        lua.new_usertype<TagComponent>("TagComponent",
            "Tag", sol::property([](TagComponent& tag) -> std::string& { return std::ref(tag.Tag); }, [](TagComponent& tag, std::string str) { tag.Tag = str; })
        );
        lua.new_usertype<TransformComponent>("TransformComponent",
            "Transform", sol::property([](TransformComponent& transform) -> Transform& { return std::ref(transform.TransformData); }, [](TransformComponent& transform, Transform trans) { transform.TransformData = trans; })
        );
        
        lua.new_usertype<SpriteRenderComponent>("SpriteRenderComponent",
            "Visible", sol::property([](SpriteRenderComponent& sprite) -> bool& { return std::ref(sprite.SpriteData.Visible); }, [](SpriteRenderComponent& sprite, bool b) { sprite.SpriteData.Visible = b; }),
            "Transparent", sol::property([](SpriteRenderComponent& sprite) -> bool& { return std::ref(sprite.SpriteData.Transparent); }, [](SpriteRenderComponent& sprite, bool b) { sprite.SpriteData.Transparent = b; }),
            "Color", sol::property([](SpriteRenderComponent& sprite) -> glm::vec4& { return std::ref(sprite.SpriteData.Color); }, [](SpriteRenderComponent& sprite, glm::vec4 color) { sprite.SpriteData.Color = color; }),
            "SourceRect", sol::property([](SpriteRenderComponent& sprite) -> Rect& { return std::ref(sprite.SpriteData.SourceRect); }, [](SpriteRenderComponent& sprite, Rect rect) { sprite.SpriteData.SourceRect = rect; }),
            "Animation", sol::property([](SpriteRenderComponent& sprite) -> Animation2D& { return std::ref(sprite.SpriteData.Animation); }, [](SpriteRenderComponent& sprite, Animation2D anim) { sprite.SpriteData.Animation = anim; }),
            "Offset", sol::property([](SpriteRenderComponent& sprite) -> Offset2D& { return std::ref(sprite.SpriteData.Offset); }, [](SpriteRenderComponent& sprite, Offset2D offset) { sprite.SpriteData.Offset = offset; })
            //TODO: ADD Texture
        );
        
        lua.new_usertype<Entity>("Entity",
            "GetChild", [](const Entity& e, std::string tag) -> Entity { return e.GetChildEntity(tag); },
            "AddChild", [](Entity& e, Entity& eChild) { e.AddChild(eChild); },
            "GetChildren", &Entity::GetChildren,
            sol::meta_function::equal_to, &Entity::operator==,
            "TagComponent", [](Entity& e) -> TagComponent& { return std::ref(e.GetComponent<TagComponent>()); },
            "TransfromComponent", [](Entity& e) -> TransformComponent& { return std::ref(e.GetComponent<TransformComponent>()); },
            "SpriteRenderComponent", [](Entity& e) -> SpriteRenderComponent& { return std::ref(e.GetComponent<SpriteRenderComponent>()); }
        );
        //TODO: Scene.GetCamera stuff
    }
}