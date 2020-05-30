#include <rwpch.h>

#include "Platform/OpenGL/OpenGLBatchRenderer.h"

namespace Rosewood
{
    class BatchRenderer{
        BatchRenderer::BatchRenderer()
        {
            
        }
        void BatchRenderer::Init()
        {
            defaultShader = Shader("Platform/OpengGL/Shaders/Default2D.glsl");
            glEnable(GL_BLEND);  
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

        }
        void BatchRenderer::Begin(OrthographicCamera& camera)
        {
            
            defaultShader.Bind();
            defaultShader.setMat4("projectionView", camera.GetViewProjection());

        }
        void BatchRenderer::End()
        {
            setupMesh();
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);

            vertices->Clear();
            indices->Clear();
            m_CurrentTexIndex = 0;
        }
        void BatchRenderer::DrawQuad(glm::vec3 pos, glm::vec2 size, float rotation, glm::vec4 uv, glm::vec4 color)
        {
            glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos)
			* glm::rotate(glm::mat4(1.0f), glm::radians(rotation), { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { size.x, size.y, 1.0f });

            //Definitely do something about textures though

            norm = glm::vec3(0.0f, 0.0f, 1.0f);
            vertices->push_back(QuadVertex(transform * glm::vec3(0.0f, 0.0f, 0.0f), norm, glm::vec2(uv.x, uv.y)), m_CurrentTexIndex);
            vertices->push_back(QuadVertex(transform * glm::vec3(0.0f, 1.0f, 0.0f), norm, glm::vec2(uv.x, uv.w)), m_CurrentTexIndex);
            vertices->push_back(QuadVertex(transform * glm::vec3(1.0f, 1.0f, 0.0f), norm, glm::vec2(uv.z, uv.w)), m_CurrentTexIndex);
            vertices->push_back(QuadVertex(transform * glm::vec3(1.0f, 0.0f, 0.0f), norm, glm::vec2(uv.z, uv.y)), m_CurrentTexIndex);

            indices->push_back(vecBack + 0);
            indices->push_back(vecBack + 1);
            indices->push_back(vecBack + 2);
            indices->push_back(vecBack + 2);
            indices->push_back(vecBack + 3);
            indices->push_back(vecBack + 0);
        }
        
        void BatchRenderer::SetTexture(Texture* texture)
        {
            if (m_CurrentTexIndex != 15)
            {
                m_CurrentTexIndex++;
                texture->Bind(m_CurrentTexIndex);
            }
            else
            {
                RW_CORE_WARN("Too many Textures bound. Try to do something else you dumbass!!")
            }
        }
    };
}
