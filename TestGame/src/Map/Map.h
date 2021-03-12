#pragma once
#include "Rosewood.h"
#include "Chunk.h"
#include <glm/glm.hpp>
#include "../Camera/CameraController.h"
#include "Tile.h"


namespace TestGame {
extern const uint32_t ChunkSize;
extern const uint32_t ChunkArea;
extern uint32_t TileSize;

    class ChunkMap
    {
    public:
        const uint32_t SizeX;
        const uint32_t SizeY;
        ChunkMap(uint32_t sizeX, uint32_t sizeY)
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
        ~ChunkMap()
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

    class Structure
    {
    public:
        const uint32_t SizeX;
        const uint32_t SizeY;

        Structure(uint32_t sizeX, uint32_t sizeY)
            : SizeX(sizeX), SizeY(sizeY)
        {
            m_Array = new uint32_t[sizeX*sizeY];
        }
        ~Structure()
        {
            delete[] m_Array;
        }

        void Set(uint32_t x, uint32_t y, uint32_t val)
        {
            m_Array[x + SizeX*y] = val;
        }
        void SetSafe(uint32_t x, uint32_t y, uint32_t val)
        {
            if(x < SizeX && x >=0 && y >= 0 && y < SizeY)
            {
                m_Array[x + SizeX*y] = val;
            }
        }
        uint32_t Get(uint32_t x, uint32_t y)
        {
            return m_Array[x + SizeX*y];
        }
        uint32_t GetSafe(uint32_t x, uint32_t y)
        {
            if(x < SizeX && x >=0 && y >= 0 && y < SizeY)
            {
                return m_Array[x + SizeX*y];
            }
            else RW_TRACE("Looking outside of the bounds!");
            return -1;
        }
    private:
        uint32_t* m_Array;
    };
    
    class Map
    {
    public:
        const uint32_t SizeX;
        const uint32_t SizeY;
        Map(uint32_t sizeX, uint32_t sizeY)
            : SizeX(sizeX), SizeY(sizeY)
        {
            m_Array = new uint32_t[sizeX*sizeY];
        }
        ~Map()
        {
            delete[] m_Array;
        }
        void Set(uint32_t x, uint32_t y, uint32_t val)
        {
            m_Array[x + SizeX*y] = val;
        }
        void SetSafe(uint32_t x, uint32_t y, uint32_t val)
        {
            if(x < SizeX && x >=0 && y >= 0 && y < SizeY)
            {
                m_Array[x + SizeX*y] = val;
            }
        }
        void SetLine(int xFrom, int yFrom, int xTo, int yTo, uint32_t val)
        {
            Rosewood::BenchmarkTimer timer("Bresenham's Algorithm");
            const bool steep = (fabs(yTo - yFrom) > fabs(xTo - xFrom));
            if(steep)
            {
                std::swap(xFrom, yFrom);
                std::swap(xTo, yTo);
            }
            
            if(xFrom > xTo)
            {
                std::swap(xFrom, xTo);
                std::swap(yFrom, yTo);
            }
            
            const float dx = xTo - xFrom;
            const float dy = fabs(yTo - yFrom);
            
            float error = dx / 2.0f;
            const int ystep = (yFrom < yTo) ? 1 : -1;
            int y = (int)yFrom;
            
            const int maxX = (int)xTo;
            
            for(int x=(int)xFrom; x<=maxX; x++)
            {
                if(steep)
                {
                    SetSafe(y,x, val);
                }
                else
                {
                    SetSafe(x,y, val);
                }
            
                error -= dy;
                if(error < 0)
                {
                    y += ystep;
                    error += dx;
                }
            }
        }
        void SetLineCustom(int xFrom, int yFrom, int xTo, int yTo, uint32_t val, const std::function<void(int, int, uint32_t)>& placeFunc)
        {
            Rosewood::BenchmarkTimer timer("Bresenham's Algorithm");
            const bool steep = (fabs(yTo - yFrom) > fabs(xTo - xFrom));
            if(steep)
            {
                std::swap(xFrom, yFrom);
                std::swap(xTo, yTo);
            }
            
            if(xFrom > xTo)
            {
                std::swap(xFrom, xTo);
                std::swap(yFrom, yTo);
            }
            
            const float dx = xTo - xFrom;
            const float dy = fabs(yTo - yFrom);
            
            float error = dx / 2.0f;
            const int ystep = (yFrom < yTo) ? 1 : -1;
            int y = (int)yFrom;
            
            const int maxX = (int)xTo;
            
            for(int x=(int)xFrom; x<=maxX; x++)
            {
                if(steep)
                {
                    placeFunc(y,x, val);
                }
                else
                {
                    placeFunc(x,y, val);
                }
            
                error -= dy;
                if(error < 0)
                {
                    y += ystep;
                    error += dx;
                }
            }
        }
        void SetRect(Rosewood::Rect bounds, uint32_t val)
        {
            Rosewood::BenchmarkTimer timer("Bounds thing");

            int left = (int)glm::clamp(bounds.Left/TileSize, 0.0f, (float)SizeX);
            int right = glm::ceil(glm::clamp(bounds.Right/TileSize, 0.0f, (float)SizeX));
            int top = (int)glm::clamp(bounds.Top/TileSize, 0.0f, (float)SizeY);
            int bottom = glm::ceil(glm::clamp(bounds.Bottom/TileSize, 0.0f, (float)SizeY));

            int tW = m_Texture->GetWidth(); // Texture width
            for(int j = top; j<bottom; j++)
            {
                for (int i = left; i < right; i++)
                {
                    SetSafe(i, j, val);
                }
            }
        }
        void SetCircle(Rosewood::Circle circle, uint32_t val)
        {
            Rosewood::BenchmarkTimer timer("Circle");
            int x0 = (int)circle.Position.x/TileSize;
            int y0 = (int)circle.Position.y/TileSize;
            int radius = (int)circle.Radius/TileSize;
            
            int f = 1 - radius;
            int ddF_x = 0;
            int ddF_y = -2 * radius;
            int x = 0;
            int y = radius;
        
            SetLine(x0, y0 + radius, x0, y0 - radius, val);
            SetLine(x0 + radius, y0, x0 - radius, y0, val);
        
            while(x < y) 
            {
                if(f >= 0) 
                {
                    y--;
                    ddF_y += 2;
                    f += ddF_y;
                }
                x++;
                ddF_x += 2;
                f += ddF_x + 1;    
                SetLine(x0 + x, y0 + y, x0 - x, y0 + y, val);

                SetLine(x0 + x, y0 - y, x0 - x, y0 - y, val);

                SetLine(x0 + y, y0 + x, x0 - y, y0 + x, val);

                SetLine(x0 + y, y0 - x, x0 - y, y0 - x, val);
            }
        }
        void SetCircleOutline(Rosewood::Circle circle, uint32_t val)
        {
            Rosewood::BenchmarkTimer timer("Circle Outline");
            int x0 = (int)circle.Position.x/TileSize;
            int y0 = (int)circle.Position.y/TileSize;
            int radius = (int)circle.Radius/TileSize;
            
            int f = 1 - radius;
            int ddF_x = 0;
            int ddF_y = -2 * radius;
            int x = 0;
            int y = radius;
        
            SetSafe(x0, y0 + radius, val);
            SetSafe(x0, y0 - radius, val);
            SetSafe(x0 + radius, y0, val);
            SetSafe(x0 - radius, y0, val);
        
            while(x < y) 
            {
                if(f >= 0) 
                {
                    y--;
                    ddF_y += 2;
                    f += ddF_y;
                }
                x++;
                ddF_x += 2;
                f += ddF_x + 1;    
                SetSafe(x0 + x, y0 + y, val);
                SetSafe(x0 - x, y0 + y, val);
                SetSafe(x0 + x, y0 - y, val);
                SetSafe(x0 - x, y0 - y, val);
                SetSafe(x0 + y, y0 + x, val);
                SetSafe(x0 - y, y0 + x, val);
                SetSafe(x0 + y, y0 - x, val);
                SetSafe(x0 - y, y0 - x, val);
            }
        }
        void SetStructure(int x, int y, Structure str)
        {
            for(int j = 0; j < str.SizeY; j++)
            {
                for(int i = 0; i < str.SizeX; i++)
                {
                    SetSafe(x + i, y + j, str.Get(i, j));
                }
            }
        }
        //TODO: Add Flood fill
        uint32_t Get(uint32_t x, uint32_t y)
        {
            return m_Array[x + SizeX*y];
        }
        uint32_t GetSafe(uint32_t x, uint32_t y)
        {
            if(x < SizeX && x >=0 && y >= 0 && y < SizeY)
            {
                return m_Array[x + SizeX*y];
            }
            else RW_TRACE("Looking outside of the bounds!");
            return -1;
        }
        Structure GetStructure(int xFrom, int yFrom, int xTo, int yTo)
        {
            Rosewood::BenchmarkTimer timer("Getting a structure");
            xFrom =         glm::clamp(xFrom, 0, (int)SizeX);
            xTo = glm::ceil(glm::clamp(xTo,   0, (int)SizeX));
            yFrom =         glm::clamp(yFrom, 0, (int)SizeY);
            yTo = glm::ceil(glm::clamp(yTo,   0, (int)SizeY));

            if(xTo < xFrom) std::swap(xTo, xFrom);
            if(yTo < yFrom) std::swap(yTo, yFrom);

            int dx = xTo - xFrom;
            int dy = yTo - yFrom;

            Structure str = Structure(dx, dy);

            for(int j = 0; j < dy; j++)
            {
                for(int i = 0; i < dx; i++)
                {
                    str.Set(i, j, Get(xFrom + i, yFrom + j));
                }
            }
            return str;
        }

        void Draw(GameCamera* camera)
        { 
            Rosewood::BenchmarkTimer timer("Map Drawing");
            
            Rosewood::Rect bounds = camera->GetBounds();
            int left = (int)glm::clamp(bounds.Left/TileSize, 0.0f, (float)SizeX);
            int right = glm::ceil(glm::clamp(bounds.Right/TileSize, 0.0f, (float)SizeX));
            int top = (int)glm::clamp(bounds.Top/TileSize, 0.0f, (float)SizeY);
            int bottom = glm::ceil(glm::clamp(bounds.Bottom/TileSize, 0.0f, (float)SizeY));

            int tW = m_Texture->GetWidth(); // Texture width
            for(int j = top; j<bottom; j++)
            {
                for (int i = left; i < right; i++)
                {
                    uint32_t tile = GET_TEX_INDEX(m_Array[i + j*SizeX]);
                    if (tile != 0)
                    {
                        int sY = (tile * TileSize / tW);
                        int sX = ((tile * TileSize) % tW) / TileSize;
                        int sX1 = sX+1;
                        int sY1 = sY+1;
                        Rosewood::BatchRenderer::DrawQuad(glm::vec3(i * TileSize, j * TileSize, 3.0f), glm::vec2(TileSize, TileSize), m_Texture, {sX * TileSize, sY * TileSize}, {sX1 * TileSize, sY1 * TileSize}, glm::vec4(1.0f));
                    }
                }
            }
        }
        void SetTexture(Rosewood::Ref<Rosewood::Texture> texture)
        {
            m_Texture = texture;
        }
        
    private:
        
        Rosewood::Ref<Rosewood::Texture> m_Texture;
        uint32_t* m_Array;
    };
}

