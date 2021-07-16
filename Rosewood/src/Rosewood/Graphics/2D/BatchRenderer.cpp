#include <rwpch.h>

#include "Rosewood/Graphics/Graphics.h"
#include "BatchRenderer.h"
#include "Rosewood/Graphics/API/VertexArray.h"

#include "Rosewood/Files/FileSystem.h"


#include <glm/gtc/matrix_transform.hpp>

namespace Rosewood
{
    const uint32_t MAX_QUADS = 10000;
    const uint32_t MAX_INDICES = MAX_QUADS * 6;
    const uint32_t MAX_VERTICES = MAX_QUADS * 4;
    const uint32_t MAX_TEXTURES = 32; //query the driver later


    struct RendererData
    {
        Ref<VertexArray> QuadVertexArray;
        Ref<VertexBuffer> QuadVertexBuffer;
        Ref<Shader> DefaultShader;
        
        uint32_t IndexCount = 0;

        QuadVertex* QuadBuffer = nullptr;
        QuadVertex* QuadPointer = nullptr;

        std::array<Ref<Texture>, MAX_TEXTURES> TextureSlots;
        uint32_t CurrentTexIndex = 1;


        Ref<Shader> CurrentShader;

        BatchRenderer::Stats RenderStats;
    };

    static RendererData s_Data;

    void BatchRenderer::Init()
    {
        s_Data.QuadVertexArray = VertexArray::Create();

        s_Data.QuadVertexBuffer = VertexBuffer::Create(MAX_VERTICES * sizeof(QuadVertex));
        
        s_Data.QuadVertexBuffer->SetLayout({
            { ShaderDataType::Float3, "aPos" },
            { ShaderDataType::Float4, "aColor" },
            { ShaderDataType::Float2, "aTexCoords" },
            { ShaderDataType::Float, "aTexIndex" }
        });
        s_Data.QuadVertexArray->AddVertexBuffer(s_Data.QuadVertexBuffer);
        
        s_Data.QuadBuffer = new QuadVertex[MAX_VERTICES];
        
        uint32_t* indices = new uint32_t[MAX_INDICES];
        
        uint32_t offset = 0;
        for (int i = 0; i < MAX_INDICES; i += 6)
        {
            indices[i + 0] = offset + 0;
            indices[i + 1] = offset + 1;
            indices[i + 2] = offset + 2;
            indices[i + 3] = offset + 2;
            indices[i + 4] = offset + 3;
            indices[i + 5] = offset + 0;
            offset += 4;
        }
        
        Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(indices, MAX_INDICES);
        
        s_Data.QuadVertexArray->SetIndexBuffer(indexBuffer);
        
        delete[] indices;

        
        s_Data.DefaultShader = Shader::Create(FileSystem::GetPath("Shaders/Default2D.glsl", FilePathType::ENGINE));
        s_Data.CurrentShader = s_Data.DefaultShader;
        

        s_Data.TextureSlots[0] = 0;
        
        
    }
    void BatchRenderer::Shutdown()
    {
        delete[] s_Data.QuadBuffer;
    }
    void BatchRenderer::SetShader(Ref<Shader> shader) //Only to be called before BatchRenderer::Begin
    {
        //End();
        s_Data.CurrentShader = shader;
        //Begin(s_Data.Camera);
    }

    void BatchRenderer::Begin(const OrthographicCamera& camera)
    {
        s_Data.CurrentShader->Bind();
        s_Data.CurrentShader->setMat4("u_ViewProjection", camera.GetViewProjection());
        BeginBatch();
    }
    void BatchRenderer::Begin(const EditorCamera& camera)
    {
        s_Data.CurrentShader->Bind();
        s_Data.CurrentShader->setMat4("u_ViewProjection", camera.GetViewProjection());
        BeginBatch();
    }
    void BatchRenderer::Begin(const Camera& camera, const glm::mat4& transform)
    {
        s_Data.CurrentShader->Bind();
        s_Data.CurrentShader->setMat4("u_ViewProjection", camera.GetProjection() * glm::inverse(transform));
        BeginBatch();
    }
    
    void BatchRenderer::BeginBatch()
    {
        s_Data.IndexCount = 0;
        s_Data.QuadPointer = s_Data.QuadBuffer;
        s_Data.CurrentTexIndex = 1;
        int Samplers[MAX_TEXTURES];
        for (int i = 0; i<MAX_TEXTURES; i++)
        {
            Samplers[i] = i;
        }
        s_Data.CurrentShader->setIntPtr("u_Textures", MAX_TEXTURES, Samplers);
    }
    void BatchRenderer::End()
    {
        uint32_t dataSize = (uint32_t)( (uint8_t*)s_Data.QuadPointer - (uint8_t*)s_Data.QuadBuffer );
        s_Data.QuadVertexBuffer->SetData(s_Data.QuadBuffer, dataSize);
        Flush();
    }
    void BatchRenderer::Flush()
    {
        for(uint32_t i = 1; i < s_Data.CurrentTexIndex; i++)
        {
            s_Data.TextureSlots[i]->Bind(i);
            
        }
        GraphicsCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.IndexCount);
        s_Data.RenderStats.DrawCount++;
    }
    void BatchRenderer::Draw() //Only to be used after End() for framebuffers and such
    {
        GraphicsCommand::DrawIndexed(s_Data.QuadVertexArray, s_Data.IndexCount);
        s_Data.RenderStats.DrawCount++;
    }

    void BatchRenderer::FlushAndReset()
    {
        End();

        BeginBatch();
    }
    void BatchRenderer::DrawQuad(const glm::mat4& transform, const glm::vec4& color)
    {
        if (s_Data.IndexCount >= MAX_INDICES)
        {
            FlushAndReset();
        }

        s_Data.QuadPointer->Position = transform * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        s_Data.QuadPointer->Color = color;
        s_Data.QuadPointer->TexCoords = glm::vec2(0.0f);
        s_Data.QuadPointer->TexIndex = 0.0f;
        s_Data.QuadPointer++;

        s_Data.QuadPointer->Position = transform * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
        s_Data.QuadPointer->Color = color;
        s_Data.QuadPointer->TexCoords = glm::vec2(0.0f);
        s_Data.QuadPointer->TexIndex = 0.0f;
        s_Data.QuadPointer++;
        
        s_Data.QuadPointer->Position = transform * glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
        s_Data.QuadPointer->Color = color;
        s_Data.QuadPointer->TexCoords = glm::vec2(0.0f);
        s_Data.QuadPointer->TexIndex = 0.0f;
        s_Data.QuadPointer++;
        
        s_Data.QuadPointer->Position = transform * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
        s_Data.QuadPointer->Color = color;
        s_Data.QuadPointer->TexCoords = glm::vec2(0.0f);
        s_Data.QuadPointer->TexIndex = 0.0f;
        s_Data.QuadPointer++;
        
        s_Data.RenderStats.QuadCount++;
        s_Data.IndexCount += 6;
    }
    void BatchRenderer::DrawQuad(const glm::mat4& transform, Ref<Texture>& texture, const glm::vec4& uv, const glm::vec4& color)
    {
        if (s_Data.IndexCount >= MAX_INDICES)
        {
            FlushAndReset();
        }

        float textureIndex = 0.0f;
        for (uint32_t i = 1; i < s_Data.CurrentTexIndex; i++)
        {
            if(*s_Data.TextureSlots[i].get() == *texture.get())
            {
                textureIndex = (float)i;
                break;
            }
        }
        if(textureIndex == 0.0f)
        {
            if (s_Data.CurrentTexIndex >= MAX_INDICES)
            {
                FlushAndReset();
            }
            textureIndex = (float)s_Data.CurrentTexIndex;
            s_Data.TextureSlots[s_Data.CurrentTexIndex] = texture;
            s_Data.CurrentTexIndex++;
        }

        s_Data.QuadPointer->Position = transform * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        s_Data.QuadPointer->Color = color;
        s_Data.QuadPointer->TexCoords = glm::vec2(uv.x, uv.w);
        s_Data.QuadPointer->TexIndex = textureIndex;
        s_Data.QuadPointer++;

        s_Data.QuadPointer->Position = transform * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
        s_Data.QuadPointer->Color = color;
        s_Data.QuadPointer->TexCoords = glm::vec2(uv.z, uv.w);
        s_Data.QuadPointer->TexIndex = textureIndex;
        s_Data.QuadPointer++;
    
        s_Data.QuadPointer->Position = transform * glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
        s_Data.QuadPointer->Color = color;
        s_Data.QuadPointer->TexCoords = glm::vec2(uv.z, uv.y);
        s_Data.QuadPointer->TexIndex = textureIndex;
        s_Data.QuadPointer++;
        
        s_Data.QuadPointer->Position = transform * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
        s_Data.QuadPointer->Color = color;
        s_Data.QuadPointer->TexCoords = glm::vec2(uv.x, uv.y);
        s_Data.QuadPointer->TexIndex = textureIndex;
        s_Data.QuadPointer++;
        
        s_Data.RenderStats.QuadCount++;
        s_Data.IndexCount += 6;
    }
    void BatchRenderer::DrawQuad(const glm::mat4& transform, Ref<Texture>& texture, const glm::vec2& fromPix, const glm::vec2& toPix, const glm::vec4& color)
    {
        float xFrom = (float)fromPix.x/texture->GetWidth();
        float yFrom = 1-(float)fromPix.y/texture->GetHeight();
        float xTo = (float)toPix.x/texture->GetWidth();
        float yTo = 1-(float)toPix.y/texture->GetHeight();
        DrawQuad(transform, texture, glm::vec4(xFrom, yTo, xTo, yFrom), color);
    }
    
    void BatchRenderer::DrawRotatedQuad(const glm::vec3& pos, const glm::vec2& size, Ref<Texture>& texture, float rotation, const glm::vec4& uv, const glm::vec4& color)
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

        DrawQuad(transform, texture, uv, color);
    }
    void BatchRenderer::DrawQuad(const glm::vec3& pos, const glm::vec2& size, Ref<Texture>& texture, const glm::vec4& uv, const glm::vec4& color)
    {
        if (s_Data.IndexCount >= MAX_INDICES)
        {
            FlushAndReset();
        }


        float textureIndex = 0.0f;
        for (uint32_t i = 1; i < s_Data.CurrentTexIndex; i++)
        {
            if(*s_Data.TextureSlots[i].get() == *texture.get())
            {
                textureIndex = (float)i;
                break;
            }
        }
        if(textureIndex == 0.0f)
        {
            if (s_Data.CurrentTexIndex >= MAX_INDICES)
            {
                FlushAndReset();
            }
            textureIndex = (float)s_Data.CurrentTexIndex;
            s_Data.TextureSlots[s_Data.CurrentTexIndex] = texture;
            s_Data.CurrentTexIndex++;
        }
        
        s_Data.QuadPointer->Position = pos;
        s_Data.QuadPointer->Color = color;
        s_Data.QuadPointer->TexCoords = glm::vec2(uv.x, uv.w);
        s_Data.QuadPointer->TexIndex = textureIndex;
        s_Data.QuadPointer++;

        s_Data.QuadPointer->Position = { pos.x + size.x, pos.y, pos.z};
        s_Data.QuadPointer->Color = color;
        s_Data.QuadPointer->TexCoords = glm::vec2(uv.z, uv.w);
        s_Data.QuadPointer->TexIndex = textureIndex;
        s_Data.QuadPointer++;
        
        s_Data.QuadPointer->Position = { pos.x + size.x, pos.y + size.y, pos.z};
        s_Data.QuadPointer->Color = color;
        s_Data.QuadPointer->TexCoords = glm::vec2(uv.z, uv.y);
        s_Data.QuadPointer->TexIndex = textureIndex;
        s_Data.QuadPointer++;
        
        s_Data.QuadPointer->Position = { pos.x, pos.y + size.y, pos.z};
        s_Data.QuadPointer->Color = color;
        s_Data.QuadPointer->TexCoords = glm::vec2(uv.x, uv.y);
        s_Data.QuadPointer->TexIndex = textureIndex;
        s_Data.QuadPointer++;
        
        s_Data.RenderStats.QuadCount++;
                
        s_Data.IndexCount += 6;
    }
    void BatchRenderer::DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color)
    {
        if (s_Data.IndexCount >= MAX_INDICES)
        {
            FlushAndReset();
        }

        s_Data.QuadPointer->Position = pos;
        s_Data.QuadPointer->Color = color;
        s_Data.QuadPointer->TexCoords = glm::vec2(0.0f);
        s_Data.QuadPointer->TexIndex = 0.0f;
        s_Data.QuadPointer++;

        s_Data.QuadPointer->Position = { pos.x + size.x, pos.y, pos.z};
        s_Data.QuadPointer->Color = color;
        s_Data.QuadPointer->TexCoords = glm::vec2(0.0f);
        s_Data.QuadPointer->TexIndex = 0.0f;
        s_Data.QuadPointer++;
        
        s_Data.QuadPointer->Position = { pos.x + size.x, pos.y + size.y, pos.z};
        s_Data.QuadPointer->Color = color;
        s_Data.QuadPointer->TexCoords = glm::vec2(0.0f);
        s_Data.QuadPointer->TexIndex = 0.0f;
        s_Data.QuadPointer++;
        
        s_Data.QuadPointer->Position = { pos.x, pos.y + size.y, pos.z};
        s_Data.QuadPointer->Color = color;
        s_Data.QuadPointer->TexCoords = glm::vec2(0.0f);
        s_Data.QuadPointer->TexIndex = 0.0f;
        s_Data.QuadPointer++;
        
        s_Data.RenderStats.QuadCount++;
        s_Data.IndexCount += 6;
    }
    void BatchRenderer::DrawQuad(const glm::vec2& pos, const glm::vec2& size, Ref<Texture>& texture, const glm::vec2& fromPix, const glm::vec2& toPix, const glm::vec4& color)
    {
        BatchRenderer::DrawQuad(glm::vec3(pos, 0.0f), size, texture, fromPix, toPix, color);
    }
    void BatchRenderer::DrawQuad(const glm::vec2& pos, const glm::vec2& size, Ref<Texture>& texture, const glm::vec4& color)
    {
        BatchRenderer::DrawQuad(glm::vec3(pos, 0.0f), size, texture, color);
    }
    void BatchRenderer::DrawQuad(const glm::vec2& pos, Ref<Texture>& texture, const glm::vec4& color)
    {
        BatchRenderer::DrawQuad(glm::vec3(pos, 0.0f), texture, color);
    }
    void BatchRenderer::DrawQuad(const glm::vec2& pos, Ref<Texture>& texture)
    {
        BatchRenderer::DrawQuad(glm::vec3(pos, 0.0f), texture);
    }
    void BatchRenderer::DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color)
    {
        BatchRenderer::DrawQuad(glm::vec3(pos, 0.0f), size, color);
    }


    void BatchRenderer::DrawQuad(const glm::vec3& pos, const glm::vec2& size, Ref<Texture>& texture, const glm::vec2& fromPix, const glm::vec2& toPix, const glm::vec4& color)
    {
        float xFrom = (float)fromPix.x/texture->GetWidth();
        float yFrom = 1-(float)fromPix.y/texture->GetHeight();
        float xTo = (float)toPix.x/texture->GetWidth();
        float yTo = 1-(float)toPix.y/texture->GetHeight();

        BatchRenderer::DrawQuad(pos, size, texture, glm::vec4(xFrom, yTo, xTo, yFrom), color);
    }
    void BatchRenderer::DrawRotatedQuad(const glm::vec3& pos, const glm::vec2& size, Ref<Texture>& texture, float rotation, const glm::vec2& fromPix, const glm::vec2& toPix, const glm::vec4& color)
    {
        float xFrom = (float)fromPix.x/texture->GetWidth();
        float yFrom = 1-(float)fromPix.y/texture->GetHeight();
        float xTo = (float)toPix.x/texture->GetWidth();
        float yTo = 1-(float)toPix.y/texture->GetHeight();

        BatchRenderer::DrawRotatedQuad(pos, size, texture, rotation, glm::vec4(xFrom, yTo, xTo, yFrom), color);
    }
    void BatchRenderer::DrawQuad(const glm::vec3& pos, const glm::vec2& size, Ref<Texture>& texture, const glm::vec4& color)
    {
        BatchRenderer::DrawQuad(pos, size, texture, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), color);
    }
    void BatchRenderer::DrawQuad(const glm::vec3& pos, Ref<Texture>& texture, const glm::vec4& color)
    {
        BatchRenderer::DrawQuad(pos, glm::vec2(texture->GetWidth(), texture->GetHeight()), texture, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), color);
    }
    void BatchRenderer::DrawQuad(const glm::vec3& pos, Ref<Texture>& texture)
    {
        BatchRenderer::DrawQuad(pos, glm::vec2(texture->GetWidth(), texture->GetHeight()), texture, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec4(1.0f));
    }


    void BatchRenderer::ResetStats()
    {
        s_Data.RenderStats.DrawCount = 0;
        s_Data.RenderStats.QuadCount = 0;
    }
    BatchRenderer::Stats BatchRenderer::GetStats()
    {
        return s_Data.RenderStats;
    }
}
