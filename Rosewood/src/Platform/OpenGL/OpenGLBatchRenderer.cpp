#include <rwpch.h>

#include "Platform/OpenGL/OpenGLBatchRenderer.h"

namespace Rosewood
{ 
    struct RendererData
    {
        GLuint QuadVA = 0;
        GLuint QuadVB = 0;
        GLuint QuadIB = 0;

        Texture WhiteTexture = Texture(1, 1);
        OrthographicCamera Camera;

        uint32_t IndexCount = 0;
        
        QuadVertex* QuadBuffer = nullptr;
        QuadVertex* QuadPointer = nullptr;

        std::array<uint32_t, MAX_TEXTURES> TextureSlots;
        uint32_t CurrentTexIndex = 0;

        Shader CurrentShader = BatchRenderer::DefaultShader;

        BatchRenderer::Stats RenderStats;
    }

    static RendererData s_Data;

    void BatchRenderer::Init()
    {
        s_Data.QuadBuffer = new QuadVertex[MaxVertexCount];

        SetupBuffers();

        glEnable(GL_BLEND);  
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

        s_Data.WhiteTexture = Texture(1, 1);
        uint32_t whiteTextureData = 0xffffffff;
        s_Data.WhiteTexture.SetData(&whiteTextureData, sizeof(uint32_t));

        s_Data.TextureSlots[0] = s_Data.WhiteTexture.GetID();
        for (size_t i = 1; i < MAX_TEXTURES; i++)
        {
            s_Data.TextureSlots[i];
        }
        
        
    }
    void BatchRenderer::Shutdown()
    {
        glDeleteVertexArrays(1, &s_Data.QuadVA);
        glDeleteBuffers(1, &s_Data.QuadVB);
        glDeleteBuffers(1, &s_Data.QuadIB);
        
        delete[] s_Data.QuadBuffer;
    }
    void BatchRenderer::SetShader(Shader& shader) //Only to be called before BatchRenderer::Begin
    {
        EndBatch();
        Flush();
        BeginBatch(s_Data.Camera, shader);
    }

    void BatchRenderer::Begin(const OrthographicCamera& camera, Shader& shader = BatchRenderer::DefaultShader)
    {
        s_Data.CurrentShader = shader;
        s_Data.CurrentShader.Bind();
        s_Data.CurrentShader.setMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
        s_Data.Camera = camera;
        int Samplers[MAX_TEXTURES];
        for (int i = 0; i<MAX_TEXTURES; i++)
        {
            Samplers[i] = i;
        }
        s_Data.CurrentShader.setIntPtr("u_Textures", 16, Samplers);
        s_Data.WhiteTexture.Bind(0);

        s_Data.QuadPointer = s_Data.QuadBuffer;
    }
    void BatchRenderer::End()
    {
        GLsizeiptr size = (uint8_t*)s_Data.QuadPointer - (uint8_t*)s_Data.QuadBuffer;
        glBindBuffer(GL_ARRAY_BUFFER, s_Data.QuadVB);
        glBufferSubData(GL_ARRAY_BUFFER, 0, s, s_Data.QuadBuffer);
    }
    void BatchRenderer::Flush()
    {
        for(uint32_t i = 0; i <= s_Data.TextureSlotIndex; i++) // My index is changed before setting the texture
        {
            glBindTextureUnit(i, s_Data.TextureSlots[i]);
        }
        glBindVertexArray(s_Data.QuadVA);
        glDrawElements(GL_TRIANGLES, s_Data.IndexCount, GL_UNSIGNED_INT, nullptr);
        s_Data.RenderStats.DrawCount++;

        s_Data.IndexCount = 0;
        s_Data.CurrentTexIndex = 0;
    }
    
    void BatchRenderer::DrawQuad(glm::vec3 pos, glm::vec2 size, Texture& texture, float rotation, glm::vec4 uv, glm::vec4 color)
    {
        if (s_Data.IndexCount >= MAX_INDICES || s_Data.CurrentTexIndex > MAX_TEXTURES-1)
        {
            EndBatch();
            Flush();
            BeginBatch(s_Data.Camera, s_Data.CurrentShader);
        }


        float textureIndex = 0.0f;
        for (uint32_t i = 1; i < s_Data.CurrentTexIndex; i++)
        {
            if(s_Data.TextureSlots[i] == texture.GetID())
            {
                textureIndex = (float)i;
                break;
            }
        }
        if(textureIndex == 0.0f)
        {
            s_Data.CurrentTexIndex++;
            textureIndex = (flaot)s_Data.CurrentTexIndex;
            s_Data.TextureSlots[s_Data.CurrentTexIndex] = texture.GetID();
        }
        
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos)
		* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
		* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        

        s_Data.QuadPointer->Position = transform * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        s_Data.QuadPointer->Color = color;
        s_Data.QuadPointer->TexCoords = glm::vec2(uv.x, uv.y);
        s_Data.QuadPointer->TexIndex = textureIndex;
        s_Data.QuadPointer++;

        s_Data.QuadPointer->Position = transform * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
        s_Data.QuadPointer->Color = color;
        s_Data.QuadPointer->TexCoords = glm::vec2(uv.x, uv.w);
        s_Data.QuadPointer->TexIndex = textureIndex;
        s_Data.QuadPointer++;
        
        s_Data.QuadPointer->Position = transform * glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
        s_Data.QuadPointer->Color = color;
        s_Data.QuadPointer->TexCoords = glm::vec2(uv.z, uv.w);
        s_Data.QuadPointer->TexIndex = textureIndex;
        s_Data.QuadPointer++;
        
        s_Data.QuadPointer->Position = transform * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
        s_Data.QuadPointer->Color = color;
        s_Data.QuadPointer->TexCoords = glm::vec2(uv.z, uv.y);
        s_Data.QuadPointer->TexIndex = textureIndex;
        s_Data.QuadPointer++;
        
        s_Data.RenderStats.QuadCount++;
        s_Data.IndexCount += 6;
    }
    void BatchRenderer::DrawQuad(glm::vec3 pos, glm::vec2 size, Texture& texture, glm::vec4 uv, glm::vec4 color)
    {
        if (s_Data.IndexCount >= MAX_INDICES || s_Data.CurrentTexIndex > MAX_TEXTURES-1)
        {
            EndBatch();
            Flush();
            BeginBatch(s_Data.Camera, s_Data.CurrentShader);
        }


        float textureIndex = 0.0f;
        for (uint32_t i = 1; i < s_Data.CurrentTexIndex; i++)
        {
            if(s_Data.TextureSlots[i] == texture.GetID())
            {
                textureIndex = (float)i;
                break;
            }
        }
        if(textureIndex == 0.0f)
        {
            s_Data.CurrentTexIndex++;
            textureIndex = (flaot)s_Data.CurrentTexIndex;
            s_Data.TextureSlots[s_Data.CurrentTexIndex] = texture.GetID();
        }
        
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos)
		* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        

        s_Data.QuadPointer->Position = transform * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        s_Data.QuadPointer->Color = color;
        s_Data.QuadPointer->TexCoords = glm::vec2(uv.x, uv.y);
        s_Data.QuadPointer->TexIndex = textureIndex;
        s_Data.QuadPointer++;

        s_Data.QuadPointer->Position = transform * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
        s_Data.QuadPointer->Color = color;
        s_Data.QuadPointer->TexCoords = glm::vec2(uv.x, uv.w);
        s_Data.QuadPointer->TexIndex = textureIndex;
        s_Data.QuadPointer++;
        
        s_Data.QuadPointer->Position = transform * glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
        s_Data.QuadPointer->Color = color;
        s_Data.QuadPointer->TexCoords = glm::vec2(uv.z, uv.w);
        s_Data.QuadPointer->TexIndex = textureIndex;
        s_Data.QuadPointer++;
        
        s_Data.QuadPointer->Position = transform * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
        s_Data.QuadPointer->Color = color;
        s_Data.QuadPointer->TexCoords = glm::vec2(uv.z, uv.y);
        s_Data.QuadPointer->TexIndex = textureIndex;
        s_Data.QuadPointer++;
        
        s_Data.RenderStats.QuadCount++;
        s_Data.IndexCount += 6;
    }
    void BatchRenderer::DrawQuad(glm::vec3 pos, glm::vec2 size, glm::vec4 color)
    {
        if (s_Data.IndexCount >= MAX_INDICES)
        {
            EndBatch();
            Flush();
            BeginBatch(s_Data.Camera, s_Data.CurrentShader);
        }
        
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos)
		* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        
        float textureIndex = 0.0f;
        

        s_Data.QuadPointer->Position = transform * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
        s_Data.QuadPointer->Color = color;
        s_Data.QuadPointer->TexCoords = glm::vec2(0.0f, 0.0f);
        s_Data.QuadPointer->TexIndex = textureIndex;
        s_Data.QuadPointer++;

        s_Data.QuadPointer->Position = transform * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
        s_Data.QuadPointer->Color = color;
        s_Data.QuadPointer->TexCoords = glm::vec2(0.0f, 1.0f);
        s_Data.QuadPointer->TexIndex = textureIndex;
        s_Data.QuadPointer++;
        
        s_Data.QuadPointer->Position = transform * glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
        s_Data.QuadPointer->Color = color;
        s_Data.QuadPointer->TexCoords = glm::vec2(1.0f, 1.0f);
        s_Data.QuadPointer->TexIndex = textureIndex;
        s_Data.QuadPointer++;
        
        s_Data.QuadPointer->Position = transform * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f);
        s_Data.QuadPointer->Color = color;
        s_Data.QuadPointer->TexCoords = glm::vec2(1.0f, 0.0f);
        s_Data.QuadPointer->TexIndex = textureIndex;
        s_Data.QuadPointer++;
        
        s_Data.RenderStats.QuadCount++;
        s_Data.IndexCount += 6;
    }

    void BatchRenderer::SetupBuffers()
    {
        // create buffers/arrays
        glCreateVertexArrays(1, &QuadVA);
        glBindVertexArray(QuadVA);

        glCreateBuffers(1, &QuadVB);
        glBindBuffer(GL_ARRAY_BUFFER, QuadVB);
        glBufferData(GL_ARRAY_BUFFER, MAX_VERTICES * sizeof(QuadVertex), nullptr, GL_DYNAMIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (void*)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (void*)offsetof(QuadVertex, Color));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (void*)offsetof(QuadVertex, TexCoords));

        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (void*)offsetof(QuadVertex, TexIndex));

        uint32_t offset = 0;
        uint32_t indices[MAX_INDICES];
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

        glCreateBuffers(1, &QuadIB);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, QuadIB);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    }

    void BatchRenderer::ResetStats()
    {
        s_Data.RenderStats.DrawCount = 0;
        s_Data.RenderStats.QuadCount = 0;
    }

}
