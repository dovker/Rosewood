#pragma once
#include "rwpch.h"
#include "Rosewood/Core.h"
#include "Model.h"
#include "Rosewood/Graphics/API/Shader.h"
#include "Rosewood/Graphics/API/Camera.h"
#include "Rosewood/Graphics/API/Texture.h"
#include "Rosewood/Graphics/API/FrameBuffer.h"
#include "Rosewood/Graphics/API/Shader.h"

namespace Rosewood {

    class Renderer
    {
    public:
        static void Init();
        static void Begin(EditorCamera& camera);
        static void End();
        
        static void Submit(Ref<Model>& model, glm::mat4 transform);
        static void Submit(Ref<Mesh>& mesh, glm::mat4 transform);

        static void Submit(Ref<Mesh>& mesh, glm::mat4 transform, Ref<Shader> shader);
        
    };

}

