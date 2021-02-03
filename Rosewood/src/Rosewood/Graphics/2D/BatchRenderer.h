#pragma once

#include <glm/glm.hpp>
#include "Rosewood/Graphics/API/Camera.h"
#include "Rosewood/Graphics/API/Shader.h"
#include "Rosewood/Graphics/API/Texture.h"
#include "Rosewood/Core.h"

namespace Rosewood
{

    struct QuadVertex {
        glm::vec3 Position;
        // color
        glm::vec4 Color;
        // texCoords
        glm::vec2 TexCoords;
        // tex index
        float TexIndex;
    };
    class BatchRenderer
    {
    public:
        
        static void Init();
        static void Begin(const OrthographicCamera& camera);
        static void End();
        static void Draw();
        static void Flush();
        static void FlushAndReset();

        //Main Draw Functions
        static void DrawQuad(glm::vec3 pos, glm::vec2 size, Ref<Texture>& texture, glm::vec4 uv, glm::vec4 color);
        static void DrawQuad(glm::vec3 pos, glm::vec2 size, Ref<Texture>& texture, float rotation, glm::vec4 uv, glm::vec4 color);
        static void DrawQuad(glm::vec3 pos, glm::vec2 size, glm::vec4 color);
        
        //Others
        static void DrawQuad(glm::vec3 pos, glm::vec2 size, Ref<Texture>& texture, glm::ivec2 fromPix, glm::ivec2 toPix, glm::vec4 color);
        static void DrawQuad(glm::vec3 pos, glm::vec2 size, glm::vec2 scale, Ref<Texture>& texture);

        static void DrawQuad(glm::vec3 pos, glm::vec2 size, Ref<Texture>& texture, glm::vec4 color);
        static void DrawQuad(glm::vec3 pos, Ref<Texture>& texture, glm::vec4 color);
        static void DrawQuad(glm::vec3 pos, Ref<Texture>& texture);

        static void SetShader(Ref<Shader> shader);

        static void Shutdown();

        struct Stats
        {
            uint32_t DrawCount = 0;
            uint32_t QuadCount = 0;
        };

        static void ResetStats();
        static Stats GetStats();
    };
}
