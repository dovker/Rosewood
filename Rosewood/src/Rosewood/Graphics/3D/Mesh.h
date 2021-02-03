#pragma once
#include "rwpch.h"
#include "Rosewood/Core.h"

#include "Rosewood/Graphics/API/Texture.h"
#include "Rosewood/Graphics/API/VertexArray.h"
#include "Rosewood/Graphics/API/Shader.h"
#include "Rosewood/Graphics/Graphics.h"
#include "Rosewood/Graphics/API/Buffer.h"



namespace Rosewood {
    
    

    class Mesh {
    public:
        // mesh Data
        std::vector<float> vertices;
        std::vector<uint32_t> indices;
        std::vector<Ref<Texture>> textures;
        Ref<VertexArray> VA;
        
        bool HasTextures() {return textures.size() > 0;}
        // constructor
        Mesh() {}
        Mesh(std::vector<float>& vertices, std::vector<uint32_t>& indices, std::vector<Ref<Texture>> textures)
            :   vertices(vertices), indices(indices), textures(textures)
        {
            VA = VertexArray::Create();
                        
            Ref<VertexBuffer> VB = VertexBuffer::Create(vertices.data(), sizeof(float)*vertices.size());
            
            BufferLayout layout = {
                { ShaderDataType::Float3, "a_Position" },
                { ShaderDataType::Float3, "a_Normal" },
                { ShaderDataType::Float3, "a_Tangent" },
                { ShaderDataType::Float3, "a_Bitangent" },
                { ShaderDataType::Float2, "a_TexCoords" },
            };
            VB->SetLayout(layout);
            VA->AddVertexBuffer(VB);
            
            Ref<IndexBuffer> IB = IndexBuffer::Create(indices.data(), indices.size());
            VA->SetIndexBuffer(IB);
            VA->Unbind();
        }
        static Ref<Mesh> Create(std::vector<float>& vertices, std::vector<uint32_t>& indices, std::vector<Ref<Texture>> textures)
        {
            return CreateRef<Mesh>(vertices, indices, textures);
        }
    };
    
}
