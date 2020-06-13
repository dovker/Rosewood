#include "rwpch.h"
#include "Texture.h"
#include "Graphics.h"

#include "Platform/OpenGL/OpenGLTexture.h"

namespace Rosewood
{
    Texture* Texture::Create(const std::string& path)
    {
        switch (Graphics::GetAPI())
        {
            case Graphics::API::None:    RW_CORE_ASSERT(false, "None is currently not supported!"); return nullptr;
            case Graphics::API::OpenGL:  return new OpenGLTexture(path);
        }
        return nullptr;
    }
    Texture* Texture::Create(uint32_t width, uint32_t height)
    {
        switch (Graphics::GetAPI())
        {
            case Graphics::API::None:    RW_CORE_ASSERT(false, "None is currently not supported!"); return nullptr;
            case Graphics::API::OpenGL:  return new OpenGLTexture(width, height);
        }
        return nullptr;
    }
}
