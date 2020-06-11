#include <rwpch.h>

#include "Platform/OpenGL/OpenGLBatchRenderer.h"

namespace Rosewood
{ 
    const uint32_t MAX_QUADS = 10000;
    const uint32_t MAX_INDICES = MAX_QUADS * 6;
    const uint32_t MAX_VERTICES = MAX_QUADS * 4;
    const uint32_t MAX_TEXTURES = 32; //query the driver later


    struct RendererData
    {
        GLuint QuadVA = 0;
        GLuint QuadVB = 0;
        GLuint QuadIB = 0;

        OrthographicCamera Camera;

        uint32_t IndexCount = 0;

        QuadVertex* QuadBuffer = nullptr;
        QuadVertex* QuadPointer = nullptr;

        std::array<uint32_t, MAX_TEXTURES> TextureSlots;
        uint32_t CurrentTexIndex = 1;

        Shader DefaultShader;

        Shader CurrentShader;

        BatchRenderer::Stats RenderStats;
    };

    static RendererData s_Data;

    void BatchRenderer::Init()
    {
        
        s_Data.QuadBuffer = new QuadVertex[MAX_VERTICES];

        SetupBuffers();
        s_Data.DefaultShader = Shader("/Users/dovydas/Documents/GitHub/Rosewood/Rosewood/src/Platform/OpenGL/Shaders/Default2D.glsl");
        s_Data.CurrentShader = s_Data.DefaultShader;

        s_Data.TextureSlots[0] = 0;
        
        
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
        End();
        s_Data.CurrentShader = shader;
        Begin(s_Data.Camera);
    }

    void BatchRenderer::Begin(const OrthographicCamera& camera)
    {
        s_Data.CurrentShader.Bind();
        s_Data.CurrentShader.setMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
        s_Data.Camera = camera;
        int Samplers[MAX_TEXTURES];
        for (int i = 0; i<MAX_TEXTURES; i++)
        {
            Samplers[i] = i;
        }
        s_Data.CurrentShader.setIntPtr("u_Textures", MAX_TEXTURES, Samplers);

        s_Data.QuadPointer = s_Data.QuadBuffer;
        s_Data.CurrentTexIndex = 1;
    }
    void BatchRenderer::End()
    {
        GLsizeiptr size = (uint8_t*)s_Data.QuadPointer - (uint8_t*)s_Data.QuadBuffer;
        glBindBuffer(GL_ARRAY_BUFFER, s_Data.QuadVB);
        glBufferSubData(GL_ARRAY_BUFFER, 0, size, s_Data.QuadBuffer);
        Flush();
    }
    void BatchRenderer::Flush()
    {
        for(uint32_t i = 1; i < s_Data.CurrentTexIndex; i++)
        {
#ifndef RW_PLATFORM_MACOS
            glBindTextureUnit(i, s_Data.TextureSlots[i]);
#else
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, s_Data.TextureSlots[i]);
#endif
        }
        glBindVertexArray(s_Data.QuadVA);
        glDrawElements(GL_TRIANGLES, s_Data.IndexCount, GL_UNSIGNED_INT, nullptr);
        s_Data.RenderStats.DrawCount++;

        s_Data.IndexCount = 0;
        s_Data.CurrentTexIndex = 1;
    }
    
    void BatchRenderer::DrawQuad(glm::vec3 pos, glm::vec2 size, Texture& texture, float rotation, glm::vec4 uv, glm::vec4 color)
    {
        if (s_Data.IndexCount >= MAX_INDICES || s_Data.CurrentTexIndex > MAX_TEXTURES-1)
        {
            End();
            Begin(s_Data.Camera);
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
            textureIndex = (float)s_Data.CurrentTexIndex;
            s_Data.TextureSlots[s_Data.CurrentTexIndex] = texture.GetID();
            s_Data.CurrentTexIndex++;
        }
        
        glm::mat4 transform = glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f });
        

        s_Data.QuadPointer->Position = transform * glm::vec4(pos.x, pos.y, pos.z, 1.0f);
        s_Data.QuadPointer->Color = color;
        s_Data.QuadPointer->TexCoords = glm::vec2(uv.x, uv.y);
        s_Data.QuadPointer->TexIndex = textureIndex;
        s_Data.QuadPointer++;

        s_Data.QuadPointer->Position = transform * glm::vec4(pos.x + size.x, pos.y, pos.z, 1.0f);
        s_Data.QuadPointer->Color = color;
        s_Data.QuadPointer->TexCoords = glm::vec2(uv.x, uv.w);
        s_Data.QuadPointer->TexIndex = textureIndex;
        s_Data.QuadPointer++;
        
        s_Data.QuadPointer->Position = transform * glm::vec4(pos.x + size.x, pos.y + size.y, pos.z, 1.0f);
        s_Data.QuadPointer->Color = color;
        s_Data.QuadPointer->TexCoords = glm::vec2(uv.z, uv.w);
        s_Data.QuadPointer->TexIndex = textureIndex;
        s_Data.QuadPointer++;
        
        s_Data.QuadPointer->Position = transform * glm::vec4(pos.x, pos.y + size.y, pos.z, 1.0f);
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
            End();
            Begin(s_Data.Camera);
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
            textureIndex = (float)s_Data.CurrentTexIndex;
            s_Data.TextureSlots[s_Data.CurrentTexIndex] = texture.GetID();
            s_Data.CurrentTexIndex++;
        }
        
        s_Data.QuadPointer->Position = pos;
        s_Data.QuadPointer->Color = color;
        s_Data.QuadPointer->TexCoords = glm::vec2(uv.x, uv.y);
        s_Data.QuadPointer->TexIndex = textureIndex;
        s_Data.QuadPointer++;

        s_Data.QuadPointer->Position = { pos.x + size.x, pos.y, pos.z};
        s_Data.QuadPointer->Color = color;
        s_Data.QuadPointer->TexCoords = glm::vec2(uv.x, uv.w);
        s_Data.QuadPointer->TexIndex = textureIndex;
        s_Data.QuadPointer++;
        
        s_Data.QuadPointer->Position = { pos.x + size.x, pos.y + size.y, pos.z};
        s_Data.QuadPointer->Color = color;
        s_Data.QuadPointer->TexCoords = glm::vec2(uv.z, uv.w);
        s_Data.QuadPointer->TexIndex = textureIndex;
        s_Data.QuadPointer++;
        
        s_Data.QuadPointer->Position = { pos.x, pos.y + size.y, pos.z};
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
            End();
            Begin(s_Data.Camera);
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

    void BatchRenderer::SetupBuffers()
    {
        // create buffers/arrays
#ifndef RW_PLATFORM_MACOS
        glCreateVertexArrays(1, &s_Data.QuadVA);
        glBindVertexArray(s_Data.QuadVA);

        glCreateBuffers(1, &s_Data.QuadVB);
        glBindBuffer(GL_ARRAY_BUFFER, s_Data.QuadVB);
        glBufferData(GL_ARRAY_BUFFER, MAX_VERTICES * sizeof(QuadVertex), nullptr, GL_DYNAMIC_DRAW);
#else
        glGenVertexArrays(1, &s_Data.QuadVA);
        glBindVertexArray(s_Data.QuadVA);

        glGenBuffers(1, &s_Data.QuadVB);
        glBindBuffer(GL_ARRAY_BUFFER, s_Data.QuadVB);
        glBufferData(GL_ARRAY_BUFFER, MAX_VERTICES * sizeof(QuadVertex), nullptr, GL_DYNAMIC_DRAW);
#endif
        

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
#ifndef RW_PLATFORM_MACOS
        glCreateBuffers(1, &s_Data.QuadIB);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_Data.QuadIB);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
#else
        glGenBuffers(1, &s_Data.QuadIB);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_Data.QuadIB);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
#endif
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
