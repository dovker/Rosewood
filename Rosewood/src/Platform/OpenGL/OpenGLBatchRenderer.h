#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <Platform/OpenGL/Shader.h>
#include <Platform/OpenGL/Texture.h>
#include <glad/glad.h>
//#include <Platform/OpenGL/Mesh.h>
#include <Rosewood/Camera.h>

namespace Rosewood
{
#define MAX_QUADS 10000
#define MAX_INDICES 60000
#define MAX_VERTICES 40000
    struct QuadVertex {
        glm::vec3 Position;
        // color
        glm::vec4 Color;
        // texCoords
        glm::vec2 TexCoords;
        // tex index
        float TexIndex;

        QuadVertex::QuadVertex(glm::vec4 pos, glm::vec4 color, glm::vec2 tex, float texInd)
            : Position(glm::vec3(pos.x, pos.y, pos.z)), Color(color), TexCoords(tex), TexIndex(texInd)
        {}
    };
    class BatchRenderer
    {
    public:
        
        //C:/dev/Rosewood/Rosewood/src/Platform/OpenGL/Shaders/Default2D.glsl
        Rosewood::Shader defaultShader = Rosewood::Shader("C:/dev/Rosewood/Rosewood/src/Platform/OpenGL/Shaders/Default2D.glsl");
        //Rosewood::Shader defaultShader = Rosewood::Shader("Platform/OpengGL/Shaders/Default2D.glsl");
        BatchRenderer() {}
        void Init();
        void Begin(const OrthographicCamera& camera);
        void End();

        void Restart(); // Ends Batch without affecting Texture idex

        void SetTexture(Texture& texture);

        void DrawQuad(glm::vec3 pos, glm::vec2 size, float rotation, glm::vec4 uv, glm::vec4 color);

    private:
        std::vector<QuadVertex> vertices;
        OrthographicCamera m_Camera;
        Texture m_WhiteTexture = Texture(1, 1);
        uint32_t m_IndexCount = 0;
        unsigned int VAO, VBO, EBO;

        unsigned int m_CurrentTexIndex = 0;
        /*  Functions    */
        void setupBuffers();
        
    };
}