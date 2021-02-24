#pragma once
#include <glm/glm.hpp>
#include "Rosewood/Graphics/API/Texture.h"
#include "Rosewood/Core.h"


#include "rwpch.h"

namespace Rosewood {

    struct Transform
    {
        glm::vec3 Position, Rotation, Scale;
        Transform(glm::vec3 pos = glm::vec3(0.0f), glm::vec3 rot = glm::vec3(0.0f), glm::vec3 scale = glm::vec3(1.0f))
            : Position(pos), Rotation(rot), Scale(scale)
        {}
    };
    struct Rect
    {
        float Left, Right, Top, Bottom, Width, Height;
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
        glm::vec2 PositionWidth() {return glm::vec2(Right, Bottom);}
        glm::vec2 RelativeWidth() {return glm::vec2(Width, Height);}
        void SetPosition(glm::vec2 Position)
        {
            Left = Position.x;
            Right = Position.x + Width;
            Top = Position.y;
            Bottom = Position.y + Height;
        }

    };
}
