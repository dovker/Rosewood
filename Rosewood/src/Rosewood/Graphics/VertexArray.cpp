#include "rwpch.h"
#include "Graphics.h"
#include "VertexArray.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Rosewood
{
    Ref<VertexArray> VertexArray::Create()
    {
        switch (Graphics::GetAPI())
        {
            case Graphics::API::None:    RW_CORE_ASSERT(false, "None is currently not supported!"); return nullptr;
            case Graphics::API::OpenGL:  return CreateRef<OpenGLVertexArray>();
        }
        return nullptr;
    }
}
