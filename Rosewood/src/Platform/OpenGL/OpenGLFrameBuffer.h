#pragma once
#include <rwpch.h>

#include "Rosewood/Graphics/FrameBuffer.h"

namespace Rosewood
{
    class OpenGLFramebuffer : public Framebuffer
    {
    public:
        OpenGLFramebuffer(const FramebufferSpecification& spec);
        virtual ~OpenGLFramebuffer();

        void Invalidate();

        virtual void Bind() override;
        virtual void Unbind() override;

        virtual void Resize(uint32_t width, uint32_t height) override;

        virtual uint32_t GetColorAttachmentRendererID() const override { return m_ColorAttachment; }
        virtual uint32_t CreateColorAttachment(uint32_t slot, TexChannelType channeType, TexChannelType format, TexChannelType dataType) override;
        virtual void RenderPrep(const uint32_t attachments[], const uint32_t count) override; // {0, 1, 2, 3, 4, ..}

        virtual const FramebufferSpecification& GetSpecification() const override { return m_Specification; }
    private:
        uint32_t m_RendererID = 0;
        uint32_t m_ColorAttachment = 0, m_DepthAttachment = 0;
        FramebufferSpecification m_Specification;
    };
}
