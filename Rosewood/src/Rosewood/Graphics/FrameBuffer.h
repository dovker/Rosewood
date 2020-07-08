#pragma once
#include <rwpch.h>

#include "Rosewood/Core.h"

namespace Rosewood
{
    struct FramebufferSpecification
    {
        uint32_t Width, Height;
        // FramebufferFormat Format =
        uint32_t Samples = 1;

        bool SwapChainTarget = false;
        
    };

    enum class TexChannelType
    {
        RGB, RGBA, RGB8, RGBA8, RGBA16F, FLOAT, UNSIGNED_BYTE
    };

    class Framebuffer
    {
    public:
        virtual ~Framebuffer() = default;

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        virtual void Resize(uint32_t width, uint32_t height) = 0;

        virtual uint32_t GetColorAttachmentRendererID() const = 0;
        virtual uint32_t CreateColorAttachment(uint32_t slot, TexChannelType channeType, TexChannelType format, TexChannelType dataType) = 0;
        virtual void RenderPrep(const uint32_t attachments[], uint32_t count) = 0; // {0, 1, 2, 3, 4, ..}

        virtual const FramebufferSpecification& GetSpecification() const = 0;

        static Ref<Framebuffer> Create(const FramebufferSpecification& spec);
    };
}
