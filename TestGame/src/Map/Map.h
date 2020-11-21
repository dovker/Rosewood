#pragma once
#include "Rosewood.h"
#include "Chunk.h"
#include <glm/glm.hpp>


namespace TestGame {
extern const uint32_t ChunkSize;
extern const uint32_t ChunkArea;
extern uint32_t TileSize;

    class Map
    {
    public:
        const uint32_t SizeX;
        const uint32_t SizeY;
        Map(uint32_t sizeX, uint32_t sizeY)
            : SizeX(sizeX), SizeY(sizeY)
        {
            m_XChunks = glm::ceil((float)SizeX/ChunkSize);
            m_YChunks = glm::ceil((float)SizeY/ChunkSize);
            m_Chunks = new Chunk*[7 * 7];
            for(int i = 0; i < m_XChunks * m_YChunks; i++)
            {
                m_Chunks[i] = new Chunk();
            }
        }
        ~Map()
        {
            delete[] m_Chunks;
        }
        void Set(uint32_t x, uint32_t y, uint32_t val)
        {
            int relX = glm::floor((float)x / ChunkSize);
            int relY = glm::floor((float)y / ChunkSize);
            if(relX < m_XChunks && relY < m_YChunks)
            {
                int cX = x % ChunkSize;
                int cY = y % ChunkSize; //TODO: OPTIMIZE
                m_Chunks[relX + m_XChunks * relY]->Set(cX, cY, val);
            }
        }
        uint32_t Get(uint32_t x, uint32_t y)
        {
            int relX = glm::floor((float)x / ChunkSize);
            int relY = glm::floor((float)y / ChunkSize);
            if(relX < m_XChunks && relY < m_YChunks)
            {
                int cX = x % ChunkSize;
                int cY = y % ChunkSize; //TODO: OPTIMIZE
                return m_Chunks[relX + m_XChunks * relY]->Get(cX, cY);
            }
            else RW_TRACE("Looking outside of the bounds!");
            return -1;
        }
        void Draw()
        {
            for(int i = 0; i < m_XChunks * m_YChunks; i++)
            {
                uint32_t xPos = (i % m_YChunks) * ChunkSize * TileSize;
                uint32_t yPos = (i / m_YChunks) * ChunkSize * TileSize;
                m_Chunks[i]->Draw(m_Texture, xPos, yPos);
            }
        }
        void SetTexture(Rosewood::Ref<Rosewood::Texture> texture)
        {
            m_Texture = texture;
        }
        
    private:
        int m_XChunks;
        int m_YChunks;
        
        Rosewood::Ref<Rosewood::Texture> m_Texture;
        Chunk** m_Chunks;
    };
    
}

