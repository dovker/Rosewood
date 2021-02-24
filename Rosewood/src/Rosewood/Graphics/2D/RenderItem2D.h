#pragma once

#include "rwpch.h"
#include <glm/glm.hpp>
#include "Rosewood/Graphics/Structs.h"
#include "Rosewood/Graphics/Graphics.h"
#include "Rosewood/Graphics/API/Texture.h"
#include "Rosewood/Application.h"
#include "Rosewood/Core.h"



namespace Rosewood
{

    class RenderItem2D
    {
    public:
        bool Visible = true;
        glm::vec4 Color;
        RenderItem2D(glm::vec4 color) { Color = color; }
        virtual void Draw(Transform transform){}
    };

    //TODO: ADD CIRCLE AND QUAD SUPPORT
    
}
