#pragma once
#include "rwpch.h"
#include "Rosewood/Graphics/API/Camera.h"
#include "Rosewood/Graphics/API/Shader.h"
#include "Rosewood/Graphics/API/Texture.h"
#include "Rosewood/Core/Core.h"

#include "Sprite.h"
#include "Rosewood/Maths/Structs.h"


namespace Rosewood
{

    class Renderer2D
    {
    public:
        static void Init();
        static void Begin(const OrthographicCamera& camera);
        static void End();

        static void Draw(Ref<Sprite> sprite, Transform transform);
        static void DrawCircle(Rosewood::Circle circle, glm::vec4 color, float depth = 0.0f);
        static void DrawRect(Rosewood::Rect rect, glm::vec4 color, float depth = 0.0f);


        static void SetShader(Ref<Shader> shader);

        static void Shutdown();
    };
    
}
