#include "rwpch.h"
#include "Texture.h"
#include "Graphics.h"

#include "Platform/OpenGL/OpenGLTexture.h"

namespace Rosewood
{
    Shader::Shader()
    {
        switch (Graphics::GetAPI())
        {
            //case RendererAPI::API::None:    RW_CORE_ASSERT(false, "None is currently not supported!"); return Texture();
            case Graphics::API::OpenGL:  return OpenGLShader();
        }
    }
    Shader::Shader(const std::string& path)
    {
        switch (Graphics::GetAPI())
        {
            //case RendererAPI::API::None:    RW_CORE_ASSERT(false, "None is currently not supported!"); return Texture();
            case Graphics::API::OpenGL:  return OpenGLShader(path);
        }
    }
    
}
