#pragma once
#include "rwpch.h"
#include "Rosewood/Graphics/API/Camera.h"
#include "Rosewood/Graphics/API/Shader.h"
#include "Rosewood/Graphics/API/Texture.h"
#include "Rosewood/Core.h"

#include "Sprite.h"
#include "Rosewood/Graphics/Structs.h"


namespace Rosewood
{

    class Renderer2D
    {
    public:
        static void Init();
        static void Begin(const OrthographicCamera& camera);
        static void End();

        static void Draw(Ref<Sprite> sprite, Transform transform);

        static void SetShader(Ref<Shader> shader);

        static void Shutdown();
    };
    
}
