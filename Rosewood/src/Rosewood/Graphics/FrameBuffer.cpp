#include "rwpch.h"
#include "Graphics.h"

#include "FrameBuffer.h"

#include "Platform/OpenGL/OpenGLFrameBuffer.h"

namespace Rosewood
{

    
    Ref<Framebuffer> Framebuffer::Create(const FramebufferSpecification& spec)
    {
        switch (Graphics::GetAPI())
        {
            case Graphics::API::None:    RW_CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
            case Graphics::API::OpenGL:  return CreateRef<OpenGLFramebuffer>(spec);
        }

        RW_CORE_ASSERT(false, "Unknown RendererAPI!");
        return nullptr;
    }
    

}
