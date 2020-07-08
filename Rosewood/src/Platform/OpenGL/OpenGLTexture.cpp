#include "rwpch.h"
#include "OpenGLTexture.h"
#include "stb_image.h"
#include <glad/glad.h>
#include <OpenGL/gl.h>
#include "OpenGL.h"

namespace Rosewood
{
	OpenGLTexture::OpenGLTexture(const std::string& path)
		: m_Path(path)
	{
		int width, height, channels;
		stbi_set_flip_vertically_on_load(1);
		unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
	
		RW_CORE_ASSERT(data, "Failed to load image!");
		m_Width = width;
		m_Height = height;

		GLenum internalFormat = 0, dataFormat = 0;
		if (channels == 4)
		{
			internalFormat = GL_RGBA8;
			dataFormat = GL_RGBA;
		}
		else if (channels == 3)
		{
			internalFormat = GL_RGB8;
			dataFormat = GL_RGB;
		}

		m_InternalFormat = internalFormat;
		m_DataFormat = dataFormat;

		RW_CORE_ASSERT(internalFormat & dataFormat, "Format not supported!");

        
        glGenTextures(1, &m_ID);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, m_ID);
        
        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_Width, m_Height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
        
        glBindTexture(GL_TEXTURE_2D, 0);

            
//            glCreateTextures(GL_TEXTURE_2D, 1, &m_ID);
//            glTextureStorage2D(m_ID, 1, internalFormat, m_Width, m_Height);
//
//            glTextureParameteri(m_ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//            glTextureParameteri(m_ID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//
//            glTextureParameteri(m_ID, GL_TEXTURE_WRAP_S, GL_REPEAT);
//            glTextureParameteri(m_ID, GL_TEXTURE_WRAP_T, GL_REPEAT);
//
//            glTextureSubImage2D(m_ID, 0, 0, 0, m_Width, m_Height, dataFormat, GL_UNSIGNED_BYTE, data);
        
        
		stbi_image_free(data);
	}
	
	OpenGLTexture::OpenGLTexture(uint32_t width, uint32_t height)
		: m_Width(width), m_Height(height)
	{
		m_InternalFormat = GL_RGBA8;
		m_DataFormat = GL_RGBA;

//            glCreateTextures(GL_TEXTURE_2D, 1, &m_ID);
//            glTextureStorage2D(m_ID, 1, m_InternalFormat, m_Width, m_Height);
//
//            glTextureParameteri(m_ID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//            glTextureParameteri(m_ID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
//
//            glTextureParameteri(m_ID, GL_TEXTURE_WRAP_S, GL_REPEAT);
//            glTextureParameteri(m_ID, GL_TEXTURE_WRAP_T, GL_REPEAT);
        uint32_t* data = new uint32_t[width*height];
        
        for (int i = 0; i< width*height; i++)
        {
            data[i] = 0xffffffff;
        }
         
        glGenTextures(1, &m_ID);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, m_ID);
        

        
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        
        glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Width, m_Height, 0, m_DataFormat, GL_UNSIGNED_BYTE, data);

                    
        glBindTexture(GL_TEXTURE_2D, 0);
        delete [] data;
        
	}




	OpenGLTexture::~OpenGLTexture()
	{
		glDeleteTextures(1, &m_ID);
	}

	void OpenGLTexture::SetData(void* data, uint32_t size)
	{
		uint32_t bpp = m_DataFormat == GL_RGBA ? 4 : 3;
		RW_CORE_ASSERT(size == m_Width * m_Height * bpp, "Data must be entire texture!");
		//glTexSubImage2D(m_ID, 0, 0, 0, m_Width, m_Height, m_DataFormat, GL_UNSIGNED_BYTE, data);
        glBindTexture(GL_TEXTURE_2D, m_ID);
        glTexImage2D(GL_TEXTURE_2D, 0, m_InternalFormat, m_Width, m_Height, 0, m_DataFormat, GL_UNSIGNED_BYTE, data);
        glBindTexture(GL_TEXTURE_2D, 0);
	}

	void OpenGLTexture::Bind(uint32_t slot) const
	{
        
        //glBindTextureUnit(slot, m_ID); //
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, m_ID);
	}
}
