#include "rwpch.h"
#include "Rosewood/Graphics/API/Shader.h"
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
            case TexChannelType::RGB16F: return GL_RGB16F;
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
        for (int i = 0; i < m_Specification.Attachments; i++)
        {
            glDeleteTextures(1, &m_ColorAttachment[i]);
        }
        glDeleteTextures(1, &m_DepthAttachment);
    }

    void OpenGLFramebuffer::Invalidate()
    {
        if (m_RendererID)
        {
            glDeleteFramebuffers(1, &m_RendererID);
            for (int i = 0; i < m_Specification.Attachments; i++)
            {
                glDeleteTextures(1, &m_ColorAttachment[i]);
            }
            glDeleteTextures(1, &m_DepthAttachment);
        }

        glGenFramebuffers(1, &m_RendererID);
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
        
        std::vector<uint32_t> attach(m_Specification.Attachments);
        
        
        for (int i = 0; i < m_Specification.Attachments; i++)
        {
            glGenTextures(1, &m_ColorAttachment[i]);
            
            glBindTexture(GL_TEXTURE_2D, m_ColorAttachment[i]);
            switch (m_Specification.Types[i]) {
                case TexChannelType::FLOAT:
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_Specification.Width, m_Specification.Height, 0, GL_RGBA, GL_FLOAT, NULL);
                    break;
                    
                case TexChannelType::UNSIGNED_BYTE:
                    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Specification.Width, m_Specification.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
                    break;
            }
            
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_ColorAttachment[i], 0);
            
            attach[i] = GL_COLOR_ATTACHMENT0 + i;
        }
        
        glDrawBuffers(m_Specification.Attachments, attach.data());
        
        
//        glGenRenderbuffers(1, &m_DepthAttachment);
//        glBindRenderbuffer(GL_RENDERBUFFER, m_DepthAttachment);
//        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_Specification.Width, m_Specification.Height);
//        glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_DepthAttachment);
        glGenTextures(1, &m_DepthAttachment);
        glBindTexture(GL_TEXTURE_2D, m_DepthAttachment);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH24_STENCIL8, m_Specification.Width, m_Specification.Height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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

    void OpenGLFramebuffer::RenderPrep(const uint32_t attachments[], const uint32_t count)
    {
		std::vector<uint32_t> attach(count);
        for(int i = 0; i < count; i++)
        {
            attach[i] = GL_COLOR_ATTACHMENT0 + i;
        }
        glDrawBuffers(count, attach.data());
        RW_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE, "Framebuffer is incomplete!");

    }
}
