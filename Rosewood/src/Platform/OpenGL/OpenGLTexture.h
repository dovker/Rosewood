#pragma once

#include <string>
#include "Rosewood/Graphics/API/Texture.h"

typedef unsigned int GLenum;

namespace Rosewood
{

    class OpenGLTexture : public Texture
    {
    public:
        // the program ID
        OpenGLTexture(const std::string& path);
        OpenGLTexture(uint32_t width, uint32_t height);
        
        ~OpenGLTexture();

        virtual uint32_t GetWidth() const override { return m_Width;  }
        virtual uint32_t GetHeight() const override { return m_Height; }
        virtual uint32_t GetID() const override { return m_ID; }
        virtual std::string& GetPath() override { return m_Path; }

        virtual void SetData(void* data, uint32_t size) override;
        
        virtual bool operator==(const Texture& other) const override
        {
            return m_ID == ((OpenGLTexture&)other).m_ID;
        }

        virtual void Bind(uint32_t slot = 0) const override;
    private:
        std::string m_Path;
        uint32_t m_Width, m_Height;
        GLenum m_InternalFormat, m_DataFormat;
        uint32_t m_ID;
    };
}
