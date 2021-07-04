#include "rwpch.h"

#include "Scene.h"
#include "Components.h"
#include "Rosewood/Maths/Structs.h"
#include "Rosewood/Core/Application.h"
#include "Entity.h"


#include <yaml-cpp/yaml.h>

namespace YAML {

	template<>
	struct convert<glm::vec3>
	{
		static Node encode(const glm::vec3& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec3& rhs)
		{
			if (!node.IsSequence() || node.size() != 3)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};

    template<>
	struct convert<glm::vec2>
	{
		static Node encode(const glm::vec2& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec2& rhs)
		{
			if (!node.IsSequence() || node.size() != 2)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			return true;
		}
	};

	template<>
	struct convert<glm::vec4>
	{
		static Node encode(const glm::vec4& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			node.SetStyle(EmitterStyle::Flow);
			return node;
		}

		static bool decode(const Node& node, glm::vec4& rhs)
		{
			if (!node.IsSequence() || node.size() != 4)
				return false;

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();
			return true;
		}
	};

}
namespace Rosewood
{
    YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec3& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
		return out;
	}

    YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec2& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << YAML::EndSeq;
		return out;
	}

	YAML::Emitter& operator<<(YAML::Emitter& out, const glm::vec4& v)
	{
		out << YAML::Flow;
		out << YAML::BeginSeq << v.x << v.y << v.z << v.w << YAML::EndSeq;
		return out;
	}
    

    static void SerializeEntity(YAML::Emitter& out, Entity entity)
	{
        if(!entity.HasComponent<UIDComponent>()) return;
		out << YAML::BeginMap; // Entity
		out << YAML::Key << "Entity" << YAML::Value << entity.GetComponent<UIDComponent>().UID; // TODO: Entity ID

		if (entity.HasComponent<TagComponent>())
		{
			out << YAML::Key << "TagComponent";
			out << YAML::BeginMap;

			auto& tag = entity.GetComponent<TagComponent>().Tag;
			out << YAML::Key << "Tag" << YAML::Value << tag;

			out << YAML::EndMap;
		}

        if (entity.HasComponent<RelationshipComponent>())
		{
			out << YAML::Key << "RelationshipComponent";
			out << YAML::BeginMap;

			auto& rc = entity.GetComponent<RelationshipComponent>();
			out << YAML::Key << "Parent" << YAML::Value << entity.GetScene()->GetEntityByID((uint32_t)rc.Parent).GetComponent<UIDComponent>().UID;

			out << YAML::EndMap;
		}

		if (entity.HasComponent<TransformComponent>())
		{
			out << YAML::Key << "TransformComponent";
			out << YAML::BeginMap;

			auto& tc = entity.GetComponent<TransformComponent>();
			out << YAML::Key << "Position" << YAML::Value << tc.TransformData.Position;
			out << YAML::Key << "Rotation" << YAML::Value << tc.TransformData.Rotation;
			out << YAML::Key << "Scale" << YAML::Value << tc.TransformData.Scale;

			out << YAML::EndMap;
		}

		if (entity.HasComponent<CameraComponent>())
		{
			out << YAML::Key << "CameraComponent";
			out << YAML::BeginMap;

			auto& cameraComponent = entity.GetComponent<CameraComponent>();
			auto& camera = cameraComponent.Camera;

			out << YAML::Key << "Camera" << YAML::Value;
			out << YAML::BeginMap;
			out << YAML::Key << "ProjectionType" << YAML::Value << (int)camera.GetProjectionType();
			out << YAML::Key << "PerspectiveFOV" << YAML::Value << camera.GetPerspectiveVerticalFOV();
			out << YAML::Key << "PerspectiveNear" << YAML::Value << camera.GetPerspectiveNearClip();
			out << YAML::Key << "PerspectiveFar" << YAML::Value << camera.GetPerspectiveFarClip();
			out << YAML::Key << "OrthographicSize" << YAML::Value << camera.GetOrthographicSize();
			out << YAML::Key << "OrthographicNear" << YAML::Value << camera.GetOrthographicNearClip();
			out << YAML::Key << "OrthographicFar" << YAML::Value << camera.GetOrthographicFarClip();
			out << YAML::EndMap;

			out << YAML::Key << "Primary" << YAML::Value << cameraComponent.Primary;
			out << YAML::Key << "FixedAspectRatio" << YAML::Value << cameraComponent.FixedAspectRatio;

			out << YAML::EndMap;
		}

		if (entity.HasComponent<SpriteRenderComponent>())
		{
			out << YAML::Key << "SpriteRenderComponent";
			out << YAML::BeginMap;

			auto& spriteRenderComponent = entity.GetComponent<SpriteRenderComponent>();
			auto& sprite = spriteRenderComponent.SpriteData;

			out << YAML::Key << "Sprite" << YAML::Value;
			out << YAML::BeginMap; //Sprite
			out << YAML::Key << "Visible" << YAML::Value << sprite.Visible;
			out << YAML::Key << "Transparent" << YAML::Value << sprite.Transparent;
			out << YAML::Key << "Color" << YAML::Value << sprite.Color;
            out << YAML::Key << "SourceRect" << YAML::Value;
			out << YAML::BeginMap; //SourceRect
            out << YAML::Key << "Position" << YAML::Value << sprite.SourceRect.Position();
			out << YAML::Key << "Size" << YAML::Value << sprite.SourceRect.Size();
            out << YAML::EndMap; //SourceRect
            out << YAML::Key << "Offset2D" << YAML::Value;
			out << YAML::BeginMap; //Offset2D
            out << YAML::Key << "Pivot" << YAML::Value << sprite.Offset.Pivot;
            out << YAML::Key << "FlippedX" << YAML::Value << sprite.Offset.FlippedX;
            out << YAML::Key << "FlippedY" << YAML::Value << sprite.Offset.FlippedY;
            out << YAML::EndMap; //Offset2D
            out << YAML::Key << "Animation2D" << YAML::Value;
			out << YAML::BeginMap; //Animation2D
			out << YAML::Key << "Speed" << YAML::Value << sprite.Animation.Speed;
			out << YAML::Key << "Frame" << YAML::Value << 0;
            out << YAML::Key << "TotalFrames" << YAML::Value << sprite.Animation.TotalFrames;
			out << YAML::Key << "Playing" << YAML::Value << sprite.Animation.Playing;
			out << YAML::Key << "Loops" << YAML::Value << sprite.Animation.Loops;
			out << YAML::EndMap; //Animation2D
			out << YAML::EndMap;

			out << YAML::Key << "AssetName" << YAML::Value << spriteRenderComponent.AssetName;

			out << YAML::EndMap;
		}
        if (entity.HasComponent<LuaScriptComponent>())
		{
			out << YAML::Key << "LuaScriptComponent";
			out << YAML::BeginMap;

			auto& luaScriptComponent = entity.GetComponent<LuaScriptComponent>();
			auto& script = luaScriptComponent.Script;

			out << YAML::Key << "TableName" << YAML::Value << script.GetTableName();
			out << YAML::Key << "AssetName" << YAML::Value << luaScriptComponent.AssetName;

			out << YAML::EndMap;
		}

		out << YAML::EndMap; // Entity
	}

    Scene::Scene(const std::string& filepath)
    {
        m_ViewportWidth = Rosewood::Application::Get().GetWindow().GetWidth();
		m_ViewportHeight = Rosewood::Application::Get().GetWindow().GetHeight();
		m_LuaState = LuaState::Create();
    }
    Scene::Scene(const TextFile& textFile)
    {
        m_ViewportWidth = Rosewood::Application::Get().GetWindow().GetWidth();
		m_ViewportHeight = Rosewood::Application::Get().GetWindow().GetHeight();
		m_LuaState = LuaState::Create();
    }

    std::string& Scene::Serialize()
    {
        
    }
    void Scene::Deserialize(const std::string& data)
    {

    }
    void Scene::Write(const std::string& filename)
    {
        
    }
}
