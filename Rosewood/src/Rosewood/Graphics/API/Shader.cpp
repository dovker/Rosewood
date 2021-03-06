#include "rwpch.h"

#include "Rosewood/Graphics/Graphics.h"
#include "Shader.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace Rosewood
{
    Ref<Shader> Shader::Create(const std::string& filepath)
    {
        switch (Graphics::GetAPI())
        {
            case Graphics::API::None:    RW_CORE_ASSERT(false, "None is currently not supported!"); return nullptr;
            case Graphics::API::OpenGL:  return CreateRef<OpenGLShader>(filepath);
        }
        return nullptr;
    }
    Ref<Shader> Shader::Create(const BinaryFile& file)
    {
        switch (Graphics::GetAPI())
        {
            case Graphics::API::None:    RW_CORE_ASSERT(false, "None is currently not supported!"); return nullptr;
            case Graphics::API::OpenGL:  return CreateRef<OpenGLShader>(file);
        }
        return nullptr;
    }
    Ref<Shader> Shader::Create(const TextFile& file)
    {
        switch (Graphics::GetAPI())
        {
            case Graphics::API::None:    RW_CORE_ASSERT(false, "None is currently not supported!"); return nullptr;
            case Graphics::API::OpenGL:  return CreateRef<OpenGLShader>(file);
        }
        return nullptr;
    }
}
