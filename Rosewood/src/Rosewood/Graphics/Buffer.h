#pragma once
#include <rwpch.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Rosewood
{
    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() {}
        
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        
        static VertexBuffer* Create(float* vertices, uint32_t size);
    };
    class IndexBuffer
    {
        virtual ~IndexBuffer() {}
        
        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        
        virtual uint32_t GetCount() const = 0;
        
        static IndexBuffer* Create(uint32_t* indices, uint32_t count);
    };
}
