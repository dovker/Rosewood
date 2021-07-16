#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/quaternion.hpp>

#include "Rosewood/Graphics/API/Texture.h"
#include "Rosewood/Core/Core.h"


#include "rwpch.h"

namespace Rosewood {
    
    struct Transform
    {
        glm::vec3 Position, Rotation, Scale;
        //Transform() = default;
        Transform(glm::vec3 pos = glm::vec3(0.0f), glm::vec3 rot = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f))
            : Position(pos), Rotation(rot), Scale(scale)
        {}
        glm::mat4 GetTransform()
        {
            glm::mat4 rotation = glm::toMat4(glm::quat(Rotation));

			return glm::translate(glm::mat4(1.0f), Position)
				* rotation
				* glm::scale(glm::mat4(1.0f), Scale);
        }
        Transform& operator +=(const Transform& t2)
        {
            this->Position += t2.Position;
            this->Rotation += t2.Rotation;
            this->Scale *= t2.Scale;
            return *this;
        }
        friend Transform operator +(Transform t1, const Transform& t2)
        {
            t1.Position += t2.Position;
            t1.Rotation += t2.Rotation;
            t1.Scale *= t2.Scale;
            return t1;
        }
    };
    struct Rect
    {
        float Left = 0.0f, Right = 0.0f, Top = 1.0f, Bottom = 1.0f, Width = 1.0f, Height = 1.0f;
        Rect() {}
        Rect(glm::vec2 Position, glm::vec2 Size)
            : Left(Position.x), Right(Position.x + Size.x), Top(Position.y), Bottom(Position.y + Size.y), Width(Size.x), Height(Size.y)
        {}
        Rect(float x, float y, float width, float height)
            : Left(x), Right(x + width), Top(y), Bottom(y + height), Width(width), Height(height)
        {}
        Rect(float z)
            : Left(z), Right(z), Top(z), Bottom(z), Width(z), Height(z)
        {}
        Rect(glm::vec2 Size)
        : Left(0.0f), Right(Size.x), Top(0.0f), Bottom(Size.y), Width(Size.x), Height(Size.y)
        {}
        Rect(Ref<Texture> Tex)
        : Left(0.0f), Right(Tex->GetWidth()), Top(0.0f), Bottom(Tex->GetHeight()), Width(Tex->GetWidth()), Height(Tex->GetHeight())
        {}
        Rect(Ref<Texture> Tex, glm::vec2 scale)
        : Left(0.0f), Right(Tex->GetWidth() * scale.x), Top(0.0f), Bottom(Tex->GetHeight() * scale.y), Width(Tex->GetWidth() * scale.x), Height(Tex->GetHeight() * scale.y)
        {}
        glm::vec2 Position() {return glm::vec2(Left, Top);}
        glm::vec2 Size() {return glm::vec2(Width, Height);}
        glm::vec2 PositionWidth() {return glm::vec2(Right, Bottom);}
        glm::vec2 RelativeWidth() {return glm::vec2(Width, Height);}
        void SetPosition(glm::vec2 Position)
        {
            Left = Position.x;
            Right = Position.x + Width;
            Top = Position.y;
            Bottom = Position.y + Height;
        }
        void SetSize(glm::vec2 Size)
        {
            Width = Size.x;
            Height = Size.y;
            Right = Left + Width;
            Bottom = Top + Height;
        }
    };
    struct Ray2D
    {
        glm::vec2 Position, Direction;
        Ray2D(glm::vec2 pos, glm::vec2 dir)
            : Position(pos), Direction(dir)
        {}
        
    };
    struct Circle
    {
        glm::vec2 Position;
        float Radius;
        Circle(glm::vec2 position, float radius)
            : Position(position), Radius(radius)
        {}
    };
}
