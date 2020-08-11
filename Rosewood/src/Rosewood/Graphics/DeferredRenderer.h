#pragma once
#include "rwpch.h"
#include "Rosewood/Core.h"
#include "Mesh.h"
#include "Shader.h"
#include "Camera.h"
#include "Texture.h"

namespace Rosewood {


    class DeferredRenderer
    {
    public:
        static void Init();
        static void Begin(glm::mat4 camera);
        static void End();
        static void DrawPointLight(glm::vec3 pos, glm::vec3 color, float intensity, float constant, float linear, float quadratic);
        static void AddPointLight(glm::vec3 pos, glm::vec3 color, float intensity, float constant, float linear, float quadratic);

        static void Submit(Ref<RenderMesh>& mesh, glm::vec3 pos, glm::vec3 scale);

        static uint32_t GetLightID();
        static uint32_t GetPosID();
        static uint32_t GetAlbedoID();
        static uint32_t GetNormalID();


    };




}

