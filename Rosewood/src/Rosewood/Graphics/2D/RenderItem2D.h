#pragma once

#include "rwpch.h"
#include <glm/glm.hpp>
#include "Rosewood/Maths/Structs.h"
#include "Rosewood/Graphics/2D/BatchRenderer.h"
#include "Rosewood/Graphics/API/Texture.h"
#include "Rosewood/Core/Core.h"



namespace Rosewood
{

    class RenderItem2D
    {
    public:
        bool Visible = true;
        bool Transparent = false;

        glm::vec4 Color = {1.0f, 1.0f, 1.0f, 1.0f};
        RenderItem2D(glm::vec4 color): Color(color)
        {
            Transparent = color.z < 1.0f;
        }
        RenderItem2D(glm::vec4 color, bool transparent): Color(color), Transparent(transparent)
        {}
        virtual void Draw(Transform transform){}
    };

    class RenderQuad : public RenderItem2D
    {
    public:
        RenderQuad(glm::vec4 color) : RenderItem2D(color) {}

        virtual void Draw(Transform transform) override
        {
            BatchRenderer::DrawQuad(transform.GetTransform(), Color);
        }
    };

    class RenderCircle : public RenderItem2D
    {
    public:
        static uint32_t CircleTextureWidth;
        static uint32_t CircleTextureHeight;
        static Ref<Texture> CircleTexture;
        RenderCircle(glm::vec4 color) : RenderItem2D(color){}

        virtual void Draw(Transform transform) override
        {
            transform.Scale.x /= CircleTextureWidth;
            transform.Scale.y /= CircleTextureHeight;
            transform.Position.x -= transform.Scale.x/2;
            transform.Position.x -= transform.Scale.x/2;

            BatchRenderer::DrawQuad(transform.GetTransform(), CircleTexture, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), Color);
        }
    };
    //TODO: ADD LINES
    //TODO: ADD POLYGONS    
}
