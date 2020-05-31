#include <rwpch.h>

#include "Platform/OpenGL/OpenGLBatchRenderer.h"

namespace Rosewood
{ 

    void BatchRenderer::Init()
    {
        glEnable(GL_BLEND);  
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
        m_WhiteTexture = Texture(1, 1);
        uint32_t whiteTextureData = 0xffffffff;
        m_WhiteTexture.SetData(&whiteTextureData, sizeof(uint32_t));
        setupBuffers();
    }
    void BatchRenderer::Begin(const OrthographicCamera& camera)
    {
        
        defaultShader.Bind();
        defaultShader.setMat4("u_ViewProjection", camera.GetViewProjectionMatrix());
        m_Camera = camera;
        int Samplers[16] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };
        defaultShader.setIntPtr("u_Textures", 16, Samplers);
        m_WhiteTexture.Bind(0);

        
    }
    void BatchRenderer::End()
    {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), &vertices[0]);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        vertices.clear();
        m_IndexCount = 0;
        m_CurrentTexIndex = 0;
    }
    void BatchRenderer::Restart()
    {
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), &vertices[0]);

        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        vertices.clear();
        m_IndexCount = 0;
        
    }
    void BatchRenderer::DrawQuad(glm::vec3 pos, glm::vec2 size, float rotation, glm::vec4 uv, glm::vec4 color)
    {
        if (vertices.size() >= MAX_QUADS * 4)
        {
            Restart();
            RW_CORE_WARN("Too many Quads. Creating a new batch");
        }
        /*
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos)
		* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
		* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });
        */
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos)
            * glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

        //Definitely do something about textures though
        size_t vecBack = vertices.size();
        vertices.push_back(QuadVertex(transform * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), color, glm::vec2(uv.x, uv.y), m_CurrentTexIndex));
        vertices.push_back(QuadVertex(transform * glm::vec4(0.0f, 1.0f, 0.0f, 1.0f), color, glm::vec2(uv.x, uv.w), m_CurrentTexIndex));
        vertices.push_back(QuadVertex(transform * glm::vec4(1.0f, 1.0f, 0.0f, 1.0f), color, glm::vec2(uv.z, uv.w), m_CurrentTexIndex));
        vertices.push_back(QuadVertex(transform * glm::vec4(1.0f, 0.0f, 0.0f, 1.0f), color, glm::vec2(uv.z, uv.y), m_CurrentTexIndex));
        m_IndexCount += 6;
    }

    void BatchRenderer::setupBuffers()
    {
        // create buffers/arrays
        glCreateVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glCreateBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, MAX_VERTICES * sizeof(QuadVertex), nullptr, GL_DYNAMIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (void*)0);

        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (void*)offsetof(QuadVertex, Color));

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (void*)offsetof(QuadVertex, TexCoords));

        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(QuadVertex), (void*)offsetof(QuadVertex, TexCoords, TexIndex));

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

        glCreateBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);


        //Something's up with vertex uffer
    }
    
    void BatchRenderer::SetTexture(Texture& texture)
    {
        if (m_CurrentTexIndex <= 15)
        {
            m_CurrentTexIndex++;
            texture.Bind(m_CurrentTexIndex);
        }
        else
        {
            RW_CORE_WARN("Too many Textures bound. Creating a new batch");
            End();
            Begin(m_Camera);
        }
    }
    

}
