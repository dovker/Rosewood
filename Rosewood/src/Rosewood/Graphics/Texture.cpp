#include "rwpch.h"
#include "Texture.h"
#include "Graphics.h"

#include "Platform/OpenGL/OpenGLTexture.h"

namespace Rosewood
{
    Texture::Texture()
    {
        switch (Graphics::GetAPI())
        {
            //case RendererAPI::API::None:    RW_CORE_ASSERT(false, "None is currently not supported!"); return Texture();
            case Graphics::API::OpenGL:  return OpenGLTexture();
        }
    }
    Texture::Texture(const std::string& path)
    {
        switch (Graphics::GetAPI())
        {
            //case RendererAPI::API::None:    RW_CORE_ASSERT(false, "None is currently not supported!"); return Texture();
            case Graphics::API::OpenGL:  return OpenGLTexture(path);
        }
    }
    Texture::Texture(uint32_t width, uint32_t height)
    {
        switch (Graphics::GetAPI())
        {
            //case RendererAPI::API::None:    RW_CORE_ASSERT(false, "None is currently not supported!"); return Texture();
            case Graphics::API::OpenGL:  return OpenGLTexture(width, height);
        }
    }
}
