#pragma once
#include <rwpch.h>

#include "Rosewood/Graphics/Buffer.h"

namespace Rosewood
{
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        
        virtual ~OpenGLVertexBuffer();
        
        virtual void Bind() const override;
        virtual void Unbind() const override;
    
    private:
        uint32_t m_ID;
    };
    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
        virtual ~OpenGLIndexBuffer();
        
        virtual void Bind() const override;
        virtual void Unbind() const override;
        
        virtual uint32_t GetCount() const { return m_Count; };
        
    private:
        uint32_t m_ID, m_Count;
    };
}
