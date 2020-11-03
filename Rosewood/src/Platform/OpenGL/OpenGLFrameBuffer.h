#pragma once
#include <rwpch.h>

#include "Rosewood/Graphics/API/FrameBuffer.h"

namespace Rosewood
{
    class OpenGLFramebuffer : public Framebuffer
    {
    public:
        OpenGLFramebuffer(const FramebufferSpecification& spec);
        virtual ~OpenGLFramebuffer();

        virtual void Invalidate();

        virtual void Bind() override;
        virtual void Unbind() override;

        virtual void Resize(uint32_t width, uint32_t height) override;
        
        virtual glm::vec2 GetSize() const override { return {m_Specification.Width, m_Specification.Height}; }

        virtual uint32_t GetColorAttachmentRendererID(uint32_t attachment = 0)  const override { return m_ColorAttachment[attachment]; }
        
        virtual uint32_t GetDepthAttachmentRendererID()  const override { return m_DepthAttachment; }
        
        virtual uint32_t CreateColorAttachment(uint32_t slot, TexChannelType channeType, TexChannelType format, TexChannelType dataType) override;
        virtual void RenderPrep(const uint32_t attachments[], const uint32_t count) override; // {0, 1, 2, 3, 4, ..}

        virtual const FramebufferSpecification& GetSpecification() const override { return m_Specification; }
    protected:
        uint32_t m_RendererID = 0;
        uint32_t m_ColorAttachment[32];
        uint32_t m_DepthAttachment = 0;
        FramebufferSpecification m_Specification;
    };

}
