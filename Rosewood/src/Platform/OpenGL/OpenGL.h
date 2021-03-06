#pragma once
#include "rwpch.h"
#include "Rosewood/Graphics/Graphics.h"

#include <glm/glm.hpp>

namespace Rosewood
{
    class OpenGL : public Graphics
    {
    public:
        
        virtual void Init() override;
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) override;
        virtual void SetClearColor(const glm::vec4& color) override;
        virtual void Clear() override;
        
        virtual void ToggleDepthTest(bool toggle) override;
        virtual void ToggleBlending(bool toggle) override;
        virtual void ToggleBackfaceCulling(bool toggle) override;


        virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) override;
        virtual void BindTexture(uint32_t ID, uint32_t slot) override;
        //static bool Old;
    };
}
