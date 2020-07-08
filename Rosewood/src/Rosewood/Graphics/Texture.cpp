#include "rwpch.h"
#include "Texture.h"
#include "Graphics.h"

#include "Platform/OpenGL/OpenGLTexture.h"

namespace Rosewood
{
    Ref<Texture> Texture::Create(const std::string& path)
    {
        switch (Graphics::GetAPI())
        {
            case Graphics::API::None:    RW_CORE_ASSERT(false, "None is currently not supported!"); return nullptr;
            case Graphics::API::OpenGL:  return CreateRef<OpenGLTexture>(path);
        }
        return nullptr;
    }
    Ref<Texture> Texture::Create(uint32_t width, uint32_t height)
    {
        switch (Graphics::GetAPI())
        {
            case Graphics::API::None:    RW_CORE_ASSERT(false, "None is currently not supported!"); return nullptr;
            case Graphics::API::OpenGL:  return CreateRef<OpenGLTexture>(width, height);
        }
        return nullptr;
    }
}
