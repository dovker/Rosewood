#include "rwpch.h"
#include "Shader.h"
#include "OpenGLFrameBuffer.h"

#include <glad/glad.h>

namespace Rosewood
{
    static uint32_t TexChannelTypeToOpenGL(TexChannelType type)
    {
        switch (type) {
            case TexChannelType::RGB:     return GL_RGB;
            case TexChannelType::RGBA:    return GL_RGBA;
            case TexChannelType::RGB8:    return GL_RGB8;
            case TexChannelType::RGBA8:   return GL_RGBA8;
            case TexChannelType::RGBA16F: return GL_RGBA16F;
            case TexChannelType::FLOAT:   return GL_FLOAT;
            case TexChannelType::UNSIGNED_BYTE:   return GL_UNSIGNED_BYTE;
        }
        RW_CORE_ASSERT(false, "Unknown Texture Channel type");
        return 0;
    }


    OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& spec)
        : m_Specification(spec)
    {
        Invalidate();
    }

    OpenGLFramebuffer::~OpenGLFramebuffer()
    {
        glDeleteFramebuffers(1, &m_RendererID);
        glDeleteTextures(1, &m_ColorAttachment);
        glDeleteTextures(1, &m_DepthAttachment);
    }

    void OpenGLFramebuffer::Invalidate()
    {
        if (m_RendererID)
        {
            glDeleteFramebuffers(1, &m_RendererID);
            glDeleteTextures(1, &m_ColorAttachment);
            glDeleteTextures(1, &m_DepthAttachment);
        }

        glGenFramebuffers(1, &m_RendererID);
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
        
        glGenTextures(1, &m_ColorAttachment);
        
        glBindTexture(GL_TEXTURE_2D, m_ColorAttachment);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Specification.Width, m_Specification.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorAttachment, 0);
        
        glGenTextures(1, &m_DepthAttachment);
        glBindTexture(GL_TEXTURE_2D, m_DepthAttachment);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_Specification.Width, m_Specification.Height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthAttachment, 0);
        
        
        RW_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGLFramebuffer::Bind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
        glViewport(0, 0, m_Specification.Width, m_Specification.Height);
    }

    void OpenGLFramebuffer::Unbind()
    {
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

    void OpenGLFramebuffer::Resize(uint32_t width, uint32_t height)
    {
        m_Specification.Width = width;
        m_Specification.Height = height;
        
        Invalidate();
    }
    

    uint32_t OpenGLFramebuffer::CreateColorAttachment(uint32_t slot, TexChannelType internalFormat, TexChannelType format, TexChannelType dataType)
    {
        uint32_t ID;
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
        
        glGenTextures(1, &ID);

        glBindTexture(GL_TEXTURE_2D, ID);
        glTexImage2D(GL_TEXTURE_2D, 0, TexChannelTypeToOpenGL(internalFormat), m_Specification.Width, m_Specification.Height, 0, TexChannelTypeToOpenGL(format), TexChannelTypeToOpenGL(dataType), nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + slot, GL_TEXTURE_2D, ID, 0);
        
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        
        RW_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");

        return ID;
    }

    void OpenGLFramebuffer::RenderPrep(const uint32_t attachments[], uint32_t count)
    {
        uint32_t attach[count];
        for(int i = 0; i < count; i++)
        {
            attach[i] = GL_COLOR_ATTACHMENT0 + i;
        }
        glDrawBuffers(count, attachments);
        RW_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");

    }
	
}
