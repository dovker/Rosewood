#pragma once

#include <string>
#include <glad/glad.h>

namespace Rosewood
{
	class Texture
	{
    public:
        // the program ID
        
        Texture() { m_ID = 0; }
        Texture(const std::string& path);
        Texture(uint32_t width, uint32_t height);
        
        
        ~Texture();

        uint32_t GetWidth() const { return m_Width; }
        uint32_t GetHeight() const { return m_Height; }
        uint32_t GetID() const { return m_ID; }

        void SetData(void* data, uint32_t size);

        void Bind(uint32_t slot = 0) const;
        
    private:
        std::string m_Path;
        uint32_t m_Width, m_Height;
        GLenum m_InternalFormat, m_DataFormat;
        uint32_t m_ID;
	};

}