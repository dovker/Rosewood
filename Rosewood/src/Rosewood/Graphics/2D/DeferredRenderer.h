#pragma once
#include "rwpch.h"
#include "Rosewood/Core.h"
#include "Mesh.h"
#include "Rosewood/Graphics/API/Shader.h"
#include "Rosewood/Graphics/API/Camera.h"
#include "Rosewood/Graphics/API/Texture.h"
#include "Rosewood/Graphics/API/FrameBuffer.h"
#include "Rosewood/Graphics/API/Shader.h"

namespace Rosewood {

    struct DecalLight
    {
        Ref<Texture> texture;
        
        glm::vec3 position;
        
        glm::vec2 size;
        
        glm::vec3 lookat;

        glm::vec3 color;
        
        DecalCamera camera;
        
        Ref<Framebuffer> depth;
        
        DecalLight() {};
        
        DecalLight(Ref<Texture> tex, glm::vec3 pos, glm::vec3 look, glm::vec3 col, glm::vec2 size)
        : texture(tex), position(pos), lookat(look),color(col), size(size)
        {
            camera = DecalCamera(-size.x/2, size.x/2, size.y/2, -size.y/2);
            camera.SetLookat(lookat);
            camera.SetPosition(position);
            depth = Framebuffer::Create({(uint32_t)size.x, (uint32_t)size.y, {FramebufferTextureFormat::DEPTH24STENCIL8}, 1, false});
            
        }
        void SetPosRot(glm::vec3 pos, glm::vec3 look)
        {
            position = pos;
            lookat = pos + look;
            camera.SetLookat(lookat);
            camera.SetPosition(position);
        }
        static Ref<DecalLight> Create(Ref<Texture> tex, glm::vec3 pos, glm::vec3 look, glm::vec3 col, glm::vec2 size)
        {
            return CreateRef<DecalLight>(tex, pos, look, col, size);
        }
    };

    class DeferredRenderer
    {
    public:
        static void Init();
        static void Begin(OrthographicCamera& camera);
        static void DrawDecals();
        static void BeginLights();
        static void End();
        
        
        static void DrawPointLight(glm::vec3 pos, glm::vec3 color, float intensity, float constant, float linear, float quadratic);
        
        static void SubmitDecalLight(Ref<DecalLight> decal);
        
        static void ReloadShaders();

        static void Submit(Ref<RenderMesh>& mesh, glm::vec3 pos, glm::vec3 scale);

        static uint32_t GetLightID();
        static uint32_t GetPosID();
        static uint32_t GetAlbedoID();
        static uint32_t GetNormalID();
        static uint32_t GetDepthID();

        
        static void SetAmbient(glm::vec3 color);
        static void SetBCS(glm::vec3 bcs);
        static void SetBWPoint(glm::vec2 bwpoint);
        static void SetExposure(float exposure);
        static void SetGamma(float gamma);



    };




}

