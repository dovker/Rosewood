#pragma once
#include <rwpch.h>

#include "Rosewood/Core/Core.h"

namespace Rosewood
{
    
    enum class FramebufferTextureFormat
    {
        None = 0,

        // Color
        RGBA8,
        RGB8,
        RGBA16F,
        RGB16F,
        // Depth/stencil
        DEPTH24STENCIL8,

        // Defaults
        Depth = DEPTH24STENCIL8
    };
    struct FramebufferTextureSpecification
    {
        FramebufferTextureSpecification() = default;
        FramebufferTextureSpecification(FramebufferTextureFormat format)
            : TextureFormat(format) {}

        FramebufferTextureFormat TextureFormat = FramebufferTextureFormat::None;
        // TODO: filtering/wrap
    };

    struct FramebufferAttachmentSpecification
    {
        FramebufferAttachmentSpecification() = default;
        FramebufferAttachmentSpecification(std::initializer_list<FramebufferTextureSpecification> attachments)
            : Attachments(attachments) {}

        std::vector<FramebufferTextureSpecification> Attachments;
    };

    struct FramebufferSpecification
    {
        uint32_t Width, Height;
        // FramebufferFormat Format =
        FramebufferAttachmentSpecification Attachments;

        uint32_t Samples = 1;
        
        bool SwapChainTarget = false;
        
    };

    

    class Framebuffer
    {
    public:
        virtual ~Framebuffer() = default;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual void Resize(uint32_t width, uint32_t height) = 0;
        
        virtual glm::vec2 GetSize() const = 0;

        virtual uint32_t GetColorAttachmentRendererID(uint32_t attachment = 0) const = 0;
        
        virtual uint32_t GetDepthAttachmentRendererID() const = 0;
        

        virtual const FramebufferSpecification& GetSpecification() const = 0;

        static Ref<Framebuffer> Create(const FramebufferSpecification& spec);

    };
}
