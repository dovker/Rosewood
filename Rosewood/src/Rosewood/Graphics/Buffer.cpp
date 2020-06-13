#include "rwpch.h"
#include "Buffer.h"
#include "Graphics.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Rosewood
{
	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
    {
        switch (Graphics::GetAPI())
        {
            case Graphics::API::None:    RW_CORE_ASSERT(false, "None is currently not supported!"); return nullptr;
            case Graphics::API::OpenGL:  return new OpenGLVertexBuffer(vertices, size);
        }
        return nullptr;
    }
    
    IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
    {
        switch (Graphics::GetAPI())
        {
            case Graphics::API::None:    RW_CORE_ASSERT(false, "None is currently not supported!"); return nullptr;
            case Graphics::API::OpenGL:  return new OpenGLIndexBuffer(indices, count);
        }
        return nullptr;
    }
}
