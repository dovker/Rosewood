#pragma once
#include "rwpch.h"
#include "Texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "BatchRenderer.h"

namespace Rosewood {
    
    class SpriteFont
    {
    public:
        SpriteFont();
        ~SpriteFont() {}

        SpriteFont(Ref<Texture>& texture, const std::string& charset, uint32_t char_width, uint32_t char_height)
            : m_Texture(texture), m_CharWidth(char_width), m_CharHeight(char_height)
        {
            uint32_t i = 0;
            for(char c : charset)
            {
                m_CharSet[c] = i;
                i++;
            }
        }
        
        //TODO: SCALE

        void DrawString(glm::vec2 pos, std::string& text, glm::vec4 color, uint32_t v_spacing = 0, uint32_t h_spacing = 0, uint32_t max_width = 100)
        {
            float cursorX = 0;
            float cursorY = 0;
            for(char c : text)
            {
                if (c != " "[0]) BatchRenderer::DrawQuad({pos.x + cursorX, pos.y + cursorY, 0.0f}, {m_CharWidth, m_CharHeight}, m_Texture, CalculateUV(c), color);
                if (cursorX + m_CharWidth + v_spacing < max_width)
                {
                    cursorX += m_CharWidth + v_spacing;
                }
                else {
                    cursorX = 0;
                    cursorY += m_CharHeight + h_spacing;
                }
            }
        }
        

        static Ref<SpriteFont> Create(Ref<Texture>& texture, const std::string& charset, uint32_t char_width, uint32_t char_height)
        {
            return CreateRef<SpriteFont>(texture, charset, char_width, char_height);
        }
    private:
        Ref<Texture> m_Texture;
        std::unordered_map<char, uint32_t> m_CharSet;
        uint32_t m_CharWidth;
        uint32_t m_CharHeight;
        
        glm::vec4 CalculateUV(char c)
        {
            uint32_t index = m_CharSet[c];
            uint32_t width = m_Texture->GetWidth() / m_CharWidth;
            uint32_t sY = index / width;
            uint32_t sX = index % width;
            float UV_Width = (float)m_CharWidth / (float)m_Texture->GetWidth();
            float UV_Height = (float)m_CharHeight / (float)m_Texture->GetHeight();

            return glm::vec4((float)sX * UV_Width, ((float)sY * UV_Height) -  UV_Height, ( (float)sX * UV_Width ) + UV_Width, (float)sY * UV_Height );
        }
    };
    
}

