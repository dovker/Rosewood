#pragma once

#include <glm/glm.hpp>
#include "Rosewood/Graphics/API/Camera.h"
#include "Rosewood/Graphics/API/Shader.h"
#include "Rosewood/Graphics/API/Texture.h"
#include "Rosewood/Core/Core.h"

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
        static void Begin(const EditorCamera& camera);
        static void Begin(const Camera& camera, const glm::mat4& transform);


        static void BeginBatch();
        static void End();
        static void Draw();
        static void Flush();
        static void FlushAndReset();

        //Main Draw Functions
        static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, Ref<Texture>& texture, const glm::vec4& uv, const glm::vec4& color);
        static void DrawQuad(const glm::mat4& transform, const glm::vec4& color);
        static void DrawQuad(const glm::mat4& transform, Ref<Texture>& texture, const glm::vec4& uv, const glm::vec4& color);

        static void DrawRotatedQuad(const glm::vec3& pos, const glm::vec2& size, Ref<Texture>& texture, float rotation, const glm::vec4&& uv, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, const glm::vec4& color);
        
        static void DrawQuad(const glm::mat4& transform, Ref<Texture>& texture, const glm::vec2& fromPix, const glm::vec2& toPix, const glm::vec4& color);

        //Others
        static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, Ref<Texture>& texture, const glm::vec2& fromPix, const glm::vec2& toPix, const glm::vec4& color);
        static void DrawRotatedQuad(const glm::vec3& pos, const glm::vec2& size, Ref<Texture>& texture, float rotation, const glm::vec2& fromPix, const glm::vec2& toPix, const glm::vec4& color);


        static void DrawQuad(const glm::vec3& pos, const glm::vec2& size, Ref<Texture>& texture, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& pos, Ref<Texture>& texture, const glm::vec4& color);
        static void DrawQuad(const glm::vec3& pos, Ref<Texture>& texture);
        
        static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, Ref<Texture>& texture, const glm::vec2& fromPix, const glm::vec2& toPix, const glm::vec4& color);
        static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, Ref<Texture>& texture, const glm::vec4& color);
        static void DrawQuad(const glm::vec2& pos, const glm::vec2& size, const glm::vec4& color);
        static void DrawQuad(const glm::vec2& pos, Ref<Texture>& texture, const glm::vec4& color);
        static void DrawQuad(const glm::vec2& pos, Ref<Texture>& texture);

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
