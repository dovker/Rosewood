#pragma once
#include <rwpch.h>


#include "Rosewood/Graphics/Graphics.h"

struct GLFWwindow;

namespace Rosewood
{
    class OpenGLContext : public GraphicsContext
    {
    public:
        OpenGLContext(GLFWwindow* windowHandle);
        
        virtual void Init() override;
        static void ForceModern();
        virtual void SwapBuffers() override;
    private:
        GLFWwindow* m_WindowHandle;
    };
}
