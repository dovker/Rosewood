#include "rwpch.h"
#include "Rosewood/Graphics/API/Shader.h"
#include "OpenGLFrameBuffer.h"

#include <glad/glad.h>

namespace Rosewood
{
        namespace Utils {

        static GLenum TextureTarget(bool multisampled)
        {
            return multisampled ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D;
        }

        static void CreateTextures(bool multisampled, uint32_t* outID, uint32_t count)
        {
            //glCreateTextures(TextureTarget(multisampled), count, outID);
            glGenTextures(count, outID);
        }

        static void BindTexture(bool multisampled, uint32_t id)
        {
            glBindTexture(TextureTarget(multisampled), id);
        }

        static void AttachColorTexture(uint32_t id, int samples, GLenum internalFormat, GLenum format, GLenum type, uint32_t width, uint32_t height, int index)
        {
            bool multisampled = samples > 1;
            if (multisampled)
            {
                glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, internalFormat, width, height, GL_FALSE);
            }
            else
            {
                glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, nullptr);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            }

            glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + index, TextureTarget(multisampled), id, 0);
        }

        static void AttachDepthTexture(uint32_t id, int samples, GLenum format, GLenum attachmentType, uint32_t width, uint32_t height)
        {
            bool multisampled = samples > 1;
            if (multisampled)
            {
                glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, format, width, height, GL_FALSE);
            }
            else
            {
                glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, GL_DEPTH_STENCIL, GL_UNSIGNED_INT_24_8, NULL);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
                
                
            }

            glFramebufferTexture2D(GL_FRAMEBUFFER, attachmentType, TextureTarget(multisampled), id, 0);
        }

        static bool IsDepthFormat(FramebufferTextureFormat format)
        {
            switch (format)
            {
                case FramebufferTextureFormat::DEPTH24STENCIL8:  return true;
            }

            return false;
        }

    }


    OpenGLFramebuffer::OpenGLFramebuffer(const FramebufferSpecification& spec)
        : m_Specification(spec)
    {
        for (auto spec : m_Specification.Attachments.Attachments)
        {
            if (!Utils::IsDepthFormat(spec.TextureFormat))
                m_ColorAttachmentSpecifications.emplace_back(spec);
            else
                m_DepthAttachmentSpecification = spec;
        }

        Invalidate();
    }

    OpenGLFramebuffer::~OpenGLFramebuffer()
    {
        glDeleteFramebuffers(1, &m_RendererID);
        glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());
        glDeleteTextures(1, &m_DepthAttachment);
    }

    void OpenGLFramebuffer::Invalidate()
    {
        if (m_RendererID)
        {
            glDeleteFramebuffers(1, &m_RendererID);
            glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());
            glDeleteTextures(1, &m_DepthAttachment);
            
            m_ColorAttachments.clear();
            m_DepthAttachment = 0;
        }

        glGenFramebuffers(1, &m_RendererID);
        glBindFramebuffer(GL_FRAMEBUFFER, m_RendererID);
        
        bool multisample = m_Specification.Samples > 1;

        // Attachments
        if (m_ColorAttachmentSpecifications.size())
        {
            m_ColorAttachments.resize(m_ColorAttachmentSpecifications.size());
            Utils::CreateTextures(multisample, m_ColorAttachments.data(), m_ColorAttachments.size());

            for (size_t i = 0; i < m_ColorAttachments.size(); i++)
            {
                Utils::BindTexture(multisample, m_ColorAttachments[i]);
                switch (m_ColorAttachmentSpecifications[i].TextureFormat)
                {
                    case FramebufferTextureFormat::RGBA8:
                        Utils::AttachColorTexture(m_ColorAttachments[i], m_Specification.Samples, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE, m_Specification.Width, m_Specification.Height, i);
                        break;
                    case FramebufferTextureFormat::RGB8:
                        Utils::AttachColorTexture(m_ColorAttachments[i], m_Specification.Samples, GL_RGB8, GL_RGB, GL_UNSIGNED_BYTE, m_Specification.Width, m_Specification.Height, i);
                        break;
                    case FramebufferTextureFormat::RGBA16F:
                        Utils::AttachColorTexture(m_ColorAttachments[i], m_Specification.Samples, GL_RGBA16F, GL_RGBA, GL_FLOAT, m_Specification.Width, m_Specification.Height, i);
                        break;
                    case FramebufferTextureFormat::RGB16F:
                        Utils::AttachColorTexture(m_ColorAttachments[i], m_Specification.Samples, GL_RGB16F, GL_RGB, GL_FLOAT, m_Specification.Width, m_Specification.Height, i);
                        break;
                }
            }
        }

        if (m_DepthAttachmentSpecification.TextureFormat != FramebufferTextureFormat::None)
        {
            glGenTextures(1, &m_DepthAttachment);
            Utils::BindTexture(multisample, m_DepthAttachment);
            switch (m_DepthAttachmentSpecification.TextureFormat)
            {
                case FramebufferTextureFormat::DEPTH24STENCIL8:
                    Utils::AttachDepthTexture(m_DepthAttachment, m_Specification.Samples, GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL_ATTACHMENT, m_Specification.Width, m_Specification.Height);
                    break;
            }
        }

        if (m_ColorAttachments.size() > 1)
        {
            //RW_CORE_ASSERT(m_ColorAttachments.size() <= 4);
            GLenum buffers[8] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3, GL_COLOR_ATTACHMENT4, GL_COLOR_ATTACHMENT5, GL_COLOR_ATTACHMENT6, GL_COLOR_ATTACHMENT7 };
            glDrawBuffers(m_ColorAttachments.size(), buffers);
        }
        else if (m_ColorAttachments.empty())
        {
            // Only depth-pass
            glDrawBuffer(GL_NONE);
        }
        
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
    
}
