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

        virtual uint32_t GetColorAttachmentRendererID(uint32_t attachment = 0)  const override { return m_ColorAttachments[attachment]; }
        
        virtual uint32_t GetDepthAttachmentRendererID()  const override { return m_DepthAttachment; }
        

        virtual const FramebufferSpecification& GetSpecification() const override { return m_Specification; }
    protected:
        uint32_t m_RendererID = 0;
        
        FramebufferSpecification m_Specification;

        std::vector<FramebufferTextureSpecification> m_ColorAttachmentSpecifications;
        FramebufferTextureSpecification m_DepthAttachmentSpecification = FramebufferTextureFormat::None;
        
        std::vector<uint32_t> m_ColorAttachments;
        uint32_t m_DepthAttachment = 0;
    };

}
