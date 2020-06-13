#pragma once

#include <string>


namespace Rosewood
{

    class OpenGLTexture : public Texture
    {
    public:
        // the program ID
        
        OpenGLTexture() const = 0;
        OpenGLTexture(const std::string& path) override;
        OpenGLTexture(uint32_t width, uint32_t height) override;
        
        
         
        virtual ~OpenGLTexture();

        virtual uint32_t GetWidth() const override { return m_Width;  }
        virtual uint32_t GetHeight() const override { return m_Height; }
        virtual uint32_t GetID() const override { return m_RendererID; }

        virtual void SetData(void* data, uint32_t size) override;

        virtual void Bind(uint32_t slot = 0) const override;
    private:
        std::string m_Path;
        uint32_t m_Width, m_Height;
        GLenum m_InternalFormat, m_DataFormat;
        uint32_t m_ID;
    };
}
