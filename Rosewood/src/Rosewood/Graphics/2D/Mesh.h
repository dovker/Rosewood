#pragma once
#include "rwpch.h"
#include "Rosewood/Core.h"

#include "Rosewood/Graphics/API/Texture.h"
#include "Rosewood/Graphics/API/VertexArray.h"
#include "Rosewood/Graphics/API/Buffer.h"


namespace Rosewood {
    
    class RenderMesh {
    public:
        // mesh Data
        std::vector<float> vertices;
        std::vector<uint32_t> indices;
        std::vector<Ref<Texture>> textures;
        Ref<VertexArray> VA;
        // constructor
        RenderMesh() {}
        RenderMesh(std::vector<float>& vertices, std::vector<uint32_t>& indices, std::vector<Ref<Texture>>& textures)
        {
            this->vertices = vertices;
            this->indices = indices;
            this->textures = textures;
            
            VA = VertexArray::Create();
                        
            Ref<VertexBuffer> VB = VertexBuffer::Create(vertices.data(), sizeof(float)*vertices.size());
            
            BufferLayout layout = {
                { ShaderDataType::Float3, "a_Position" },

                { ShaderDataType::Float2, "a_TexCoords" },
                

            };
            VB->SetLayout(layout);
            VA->AddVertexBuffer(VB);
            
            Ref<IndexBuffer> IB = IndexBuffer::Create(indices.data(), indices.size());
            VA->SetIndexBuffer(IB);
            VA->Unbind();

        }
        static Ref<RenderMesh> Create(std::vector<float> vertices, std::vector<uint32_t> indices, std::vector<Ref<Texture>> textures)
        {
            return CreateRef<RenderMesh>(vertices, indices, textures);
        }
        
        static Ref<RenderMesh> CreateFoldedQuad(std::vector<Ref<Texture>> textures, float foldline)
        {
            std::vector<float> vertices{
            0.0f, 0.0f,     0.0f,        0.0f, 0.0f,
            0.0f, foldline, 0.0f,        0.0f, foldline,
            1.0f, foldline, 0.0f,        1.0f, foldline,
            1.0f, 0.0f,     0.0f,        1.0f, 0.0f,
            0.0f, 1.0f,    -foldline,    0.0f, 1.0f,
            1.0f, 1.0f,    -foldline,    1.0f, 1.0f};
            std::vector<uint32_t> indices
            {0, 1, 2, 2, 3, 0,
             1, 4, 5, 5, 2, 1};
            return CreateRef<RenderMesh>(vertices, indices, textures);
        }
        static Ref<RenderMesh> CreateFlatQuad(std::vector<Ref<Texture>> textures)
        {
            std::vector<float> vertices{
            0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 1.0f, 0.0f};
            std::vector<uint32_t> indices
            {0, 1, 2, 2, 3, 0};
            return CreateRef<RenderMesh>(vertices, indices, textures);
        }
        static Ref<RenderMesh> CreatePerpendicularQuad(std::vector<Ref<Texture>> textures)
        {
            std::vector<float> vertices{
            0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 0.0f, 1.0f, 0.0f};
            std::vector<uint32_t> indices
            {0, 1, 2, 2, 3, 0};
            return CreateRef<RenderMesh>(vertices, indices, textures);
        }
        
        static Ref<VertexArray> CreateCircleVA(int segments)
        {
            uint32_t vertexSegments = segments + 2;
            uint32_t numberOfVertices = 3*vertexSegments;
            
            float twoPi = glm::two_pi<float>();
            
            std::vector<uint32_t> indices(vertexSegments*3);
            
            std::vector<float> circleVertices(numberOfVertices);
            
            uint32_t currentIndex = 0;
            uint32_t currentVIndex = 3;

            
            circleVertices[0] = 0.0f;
            circleVertices[1] = 0.0f;
            circleVertices[2] = 0.0f;
            
            for (int i = 1; i < numberOfVertices/3; i++)
            {
                circleVertices[currentVIndex] = cos(i*twoPi / segments);
                circleVertices[currentVIndex + 1] = sin(i*twoPi / segments);
                circleVertices[currentVIndex + 2] = 0.0f;
                
                indices[currentIndex] = 0;
                indices[currentIndex + 1] = i-1;
                indices[currentIndex + 2] = i;
                currentIndex+=3;
                currentVIndex += 3;
            }
            Ref<VertexArray> VA = VertexArray::Create();
            
            Ref<VertexBuffer> VB = VertexBuffer::Create(circleVertices.data(), sizeof(float)*circleVertices.size());
            BufferLayout layout = {
                { ShaderDataType::Float3, "a_Position" }
            };
            VB->SetLayout(layout);
            VA->AddVertexBuffer(VB);

            Ref<IndexBuffer> IB = IndexBuffer::Create(indices.data(), indices.size());
            VA->SetIndexBuffer(IB);
            
            return VA;
        }
        static Ref<VertexArray> CreateCubeVA()
        {
                    
            std::vector<uint32_t> indices = //36
            {
                0, 1, 2,  2, 3, 0,
                3, 2, 6,  6, 7, 3,
                7, 6, 5,  5, 4, 7,
                4, 5, 1,  1, 0, 4,
                1, 5, 6,  6, 2, 1,
                4, 0, 3,  3, 7, 4,
            };
            
            std::vector<float> circleVertices = //8
            {
                -0.5f, -0.5f, 0.5f,
                -0.5f, 0.5f, 0.5f,
                0.5f, 0.5f, 0.5f,
                0.5f, -0.5f, 0.5f,
                
                -0.5f, -0.5f, -0.5f,
                -0.5f, 0.5f, -0.5f,
                0.5f, 0.5f, -0.5f,
                0.5f, -0.5f, -0.5f,
            };
            
            
            Ref<VertexArray> VA = VertexArray::Create();
            
            Ref<VertexBuffer> VB = VertexBuffer::Create(circleVertices.data(), sizeof(float)*circleVertices.size());
            BufferLayout layout = {
                { ShaderDataType::Float3, "a_Position" }
            };
            VB->SetLayout(layout);
            VA->AddVertexBuffer(VB);

            Ref<IndexBuffer> IB = IndexBuffer::Create(indices.data(), indices.size());
            VA->SetIndexBuffer(IB);
            
            return VA;
        }
        static Ref<VertexArray> CreateCircleVAExt(int segments)
        {
            uint32_t vertexSegments = segments + 2;
            uint32_t numberOfVertices = 5*vertexSegments;
            
            float twoPi = glm::two_pi<float>();
            
            std::vector<uint32_t> indices(vertexSegments*3);
            
            std::vector<float> circleVertices(numberOfVertices);
            
            uint32_t currentIndex = 0;
            uint32_t currentVIndex = 5;

            
            circleVertices[0] = 0.0f;
            circleVertices[1] = 0.0f;
            circleVertices[2] = 0.0f;
            circleVertices[3] = 0.0f;
            circleVertices[4] = 0.0f;

            
            for (int i = 1; i < numberOfVertices/5; i++)
            {
                circleVertices[currentVIndex] = cos(i*twoPi / segments);
                circleVertices[currentVIndex + 1] = sin(i*twoPi / segments);
                circleVertices[currentVIndex + 2] = 0.0f;
                circleVertices[currentVIndex + 3] = circleVertices[currentVIndex];
                circleVertices[currentVIndex + 4] = circleVertices[currentVIndex + 1];
                indices[currentIndex] = 0;
                indices[currentIndex + 1] = i-1;
                indices[currentIndex + 2] = i;
                currentIndex+=3;
                currentVIndex += 5;
            }
            Ref<VertexArray> VA = VertexArray::Create();
            
            Ref<VertexBuffer> VB = VertexBuffer::Create(circleVertices.data(), sizeof(float)*circleVertices.size());
            BufferLayout layout = {
                { ShaderDataType::Float3, "a_Position" },
                { ShaderDataType::Float2, "a_TexCoords" }
            };
            VB->SetLayout(layout);
            VA->AddVertexBuffer(VB);

            Ref<IndexBuffer> IB = IndexBuffer::Create(indices.data(), indices.size());
            VA->SetIndexBuffer(IB);
            VA->Unbind();
            return VA;
        }
    };
}
