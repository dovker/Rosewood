#include <rwpch.h>

#include "Platform/OpenGL/OpenGLBatchRenderer.h"

namespace Rosewood
{
    class BatchRenderer{
        BatchRenderer()
        {
            defaultShader.Use();
        }
        void Begin(glm::mat4 projection)
        {
            


        }
        void End()
        {

            setupMesh();
        }
        void DrawQuad(glm::vec2 pos, Texture texture, glm::vec4 uv, glm::vec4 color)
        {
            norm = glm::vec3(0.0f, 0.0f, 1.0f);
            vertices->push_back(Vertex(pos + glm::vec3(0.0f, 0.0f, 0.0f), norm, glm::vec2(uv.x, uv.y)));
            vertices->push_back(Vertex(pos + glm::vec3(0.0f, 1.0f, 0.0f), norm, glm::vec2(uv.x, uv.w)));
            vertices->push_back(Vertex(pos + glm::vec3(1.0f, 1.0f, 0.0f), norm, glm::vec2(uv.z, uv.w));
            vertices->push_back(Vertex(pos + glm::vec3(1.0f, 0.0f, 0.0f), norm, glm::vec2(uv.z, uv.y)));
        }
        
    };
}
