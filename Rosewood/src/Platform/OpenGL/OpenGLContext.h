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
        virtual void SwapBuffers() override;
    private:
        GLFWwindow* m_WindowHandle;
    };
}
