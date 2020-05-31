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
#define MAX_TEXTURES 16

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
        static Rosewood::Shader DefaultShader = Rosewood::Shader("C:/dev/Rosewood/Rosewood/src/Platform/OpenGL/Shaders/Default2D.glsl");
        //Rosewood::Shader defaultShader = Rosewood::Shader("Platform/OpengGL/Shaders/Default2D.glsl");
        
        static void Init();
        static void Begin(const OrthographicCamera& camera, Shader& shader = BatchRenderer::DefaultShader);
        static void End();
        static void Flush();

        static void Restart(); // Ends Batch without affecting Texture idex

        static void SetTexture(Texture& texture);

        static void DrawQuad(glm::vec3 pos, glm::vec2 size, Texture& texture, glm::vec4 uv, glm::vec4 color);
        static void DrawQuad(glm::vec3 pos, glm::vec2 size, Texture& texture, float rotation, glm::vec4 uv, glm::vec4 color);
        static void DrawQuad(glm::vec3 pos, glm::vec2 size, glm::vec4 color);

        static void SetShader(Shader& shader);

        static void SetupBuffers();

        static void Shutdown();

        struct Stats
        {
            uint32_t DrawCount = 0;
            uint32_t QuadCount = 0;
        };

        static void ResetStats();
        
    };
}