#pragma once
#include <rwpch.h>

#include <glm/glm.hpp>

namespace Rosewood
{
    class Graphics
    {
    public:
        enum class API
        {
            None = 0, OpenGL = 1
        };
        
        virtual void Init() = 0;
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height) = 0;
        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void Clear() = 0;

        virtual void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t indexCount = 0) = 0;

        static API GetAPI() { return s_API; }
        
        static Scope<Graphics> Create();
    private:
        static API s_API;
    };

    class GraphicsCommand
    {
    public:
        static void Init()
        {
            s_Graphics->Init();
        }

        static void SetViewport(uint32_t x, uint32_t y, uint32_t width, uint32_t height)
        {
            s_Graphics->SetViewport(x, y, width, height);
        }

        static void SetClearColor(const glm::vec4& color)
        {
            s_Graphics->SetClearColor(color);
        }

        static void Clear()
        {
            s_Graphics->Clear();
        }

        static void DrawIndexed(const Ref<VertexArray>& vertexArray, uint32_t count = 0)
        {
            s_Graphics->DrawIndexed(vertexArray, count);
        }
    private:
        static Scope<Graphics> s_Graphics;
    };

    class GraphicsContext
    {
        
    public:
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;

        
    };
}
