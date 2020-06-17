#include "rwpch.h"
#include "OpenGLContext.h"
#include <glad/glad.h>
#include "GLFW/glfw3.h"


namespace Rosewood
{
    OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
        : m_WindowHandle(windowHandle)
    {
        
    }
    void OpenGLContext::ForceModern()
    {
        #ifdef RW_PLATFORM_MACOS
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        RW_CORE_INFO("Mac OS");
        #endif
    }
	void OpenGLContext::Init()
    {
        
        
        glfwMakeContextCurrent(m_WindowHandle);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        RW_CORE_ASSERT(status, "Glad was not initialized!");
        
        RW_CORE_INFO("OpenGL Version: {0}", glGetString(GL_VERSION));
    }
    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_WindowHandle);
    }
}
