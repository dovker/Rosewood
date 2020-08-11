#pragma once
#include "rwpch.h"
#include "Rosewood/Core.h"

#include "Texture.h"
#include "VertexArray.h"
#include "Buffer.h"


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
        RenderMesh(std::vector<float> vertices, std::vector<uint32_t> indices, std::vector<Ref<Texture>> textures)
        {
            this->vertices = vertices;
            this->indices = indices;
            this->textures = textures;
            
            VA = VertexArray::Create();
                        
            Ref<VertexBuffer> VB = VertexBuffer::Create(vertices.data(), sizeof(vertices));
            
            BufferLayout layout = {
                { ShaderDataType::Float3, "a_Position" },
                { ShaderDataType::Float2, "a_TexCoords" }

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
    };
}
