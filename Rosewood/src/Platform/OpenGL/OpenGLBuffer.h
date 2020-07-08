#pragma once
#include <rwpch.h>

#include "Rosewood/Graphics/Buffer.h"

namespace Rosewood
{
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float* vertices, uint32_t size);
        OpenGLVertexBuffer(Vertex* vertices, uint32_t size);

        OpenGLVertexBuffer(uint32_t size);
        
        virtual ~OpenGLVertexBuffer();
        
        virtual void Bind() const override;
        virtual void Unbind() const override;
        
        virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
        virtual const BufferLayout& GetLayout() const override { return m_Layout; };
        
        virtual void SetData(const void* data, uint32_t size) override;
    
    private:
        uint32_t m_ID;
        BufferLayout m_Layout;
    };
    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
        virtual ~OpenGLIndexBuffer();
        
        virtual void Bind() const override;
        virtual void Unbind() const override;
        
        virtual uint32_t GetCount() const override { return m_Count; };
        
    private:
        uint32_t m_ID, m_Count;
    };
}
