#pragma once
#include "Rosewood.h"
#include "Map.h"

namespace TestGame {
extern const uint32_t ChunkSize;
extern const uint32_t ChunkArea;
extern uint32_t TileSize;

    class Chunk
    {
    public:
        Chunk()
            : m_Size(ChunkSize)
        {
            for (int i = 0; i < ChunkArea; i++)
            {
                m_Array[i] = 0;
            }
        }
        ~Chunk()
        {
            //delete [] m_Array;
        }
        void Set(uint32_t x, uint32_t y, uint32_t value)
        {
            if (y < m_Size && x < m_Size)
            {
                m_Array[x + m_Size * y] = value;
            }
            else RW_TRACE("Looking outside of the bounds!");
        }
        uint32_t Get(uint32_t x, uint32_t y)
        {
            if (y < m_Size && x < m_Size)
            {
                return m_Array[x + m_Size * y];
            }
            else RW_TRACE("Looking outside of the bounds!");
            return -1;
        }
        void Draw(Rosewood::Ref<Rosewood::Texture> texture, uint32_t xPos, uint32_t yPos)
        {
            int tW = texture->GetWidth(); // Texture width
            
            for (int i = 0; i < ChunkSize; i++)
            {
                for(int j = 0; j<ChunkSize; j++)
                {
                    uint32_t tile = m_Array[i + j*m_Size];
                    if (tile != 0)
                    {
                        int sY = (tile * TileSize / tW);
                        int sX = ((tile * TileSize) % tW) / TileSize;
                        int sX1 = sX+1;
                        int sY1 = sY+1;
                        Rosewood::BatchRenderer::DrawQuad(glm::vec3(xPos + i * TileSize, yPos + j * TileSize, 3.0f), glm::vec2(TileSize, TileSize), texture, {sX * TileSize, sY * TileSize}, {sX1 * TileSize, sY1 * TileSize}, glm::vec4(1.0f));
                    }
                }
            }
        }
    private:
        uint32_t m_Size;
        uint32_t m_Array[16*16];

    };
    
}

