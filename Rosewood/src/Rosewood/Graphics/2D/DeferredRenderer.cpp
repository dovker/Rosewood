#include "rwpch.h"

#include "DeferredRenderer.h"
#include "Rosewood/Graphics/Graphics.h"
#include "Rosewood/Core/Application.h"



namespace Rosewood
{

    
    struct PointLight
    {
        glm::vec3 position;
        
        glm::vec3 color;
        
        float intensity;
        
        float constant;
        float linear;
        float quadratic;
        
        PointLight() {};
        
        PointLight(glm::vec3 pos, glm::vec3 col, float intens,  float cons, float lin, float quadr)
        : position(pos), color(col), intensity(intens), constant(cons), linear(lin), quadratic(quadr)
        {}
    };

    struct RenderItem
    {
        Ref<RenderMesh>& mesh; glm::vec3 pos; glm::vec3 scale;
        RenderItem(Ref<RenderMesh>& mesh, glm::vec3 pos, glm::vec3 scale)
        : mesh(mesh), pos(pos), scale(scale)
        {}
    };
    
    

    struct GBuffer
    {
        Ref<Framebuffer> FrameGBuffer;
        
        Ref<Framebuffer> FrameLightBuffer;

        
        Ref<Shader> GBufferShader;
        Ref<Shader> LightBufferShader;
        Ref<Shader> FinalShader;
        Ref<Shader> DecalShader;
        Ref<Shader> DepthRenderShader;


        uint32_t AlbedoSpec;
        uint32_t Position;
        uint32_t Normal;
        uint32_t Light;
        uint32_t Depth;
        
        Ref<VertexArray> QuadVA;
        Ref<VertexArray> CubeVA;
        Ref<VertexArray> CircleVA;
        
        glm::vec3 Ambient;
        float Exposure;
        float Gamma;
        glm::vec3 BCS; //Brightness, contrast, Saturation
        glm::vec2 BWPoint; //Black point and White point
        
        std::vector<RenderItem> RenderQueue;
        std::vector<Ref<DecalLight>> DecalQueue;

        glm::mat4 Camera;
        OrthographicCamera CameraPtr;
    };

    static GBuffer s_Buffer;

    float CalculateRadius(const PointLight &light)
    {
        float lightMax  = std::fmaxf(std::fmaxf(light.color.r * light.intensity, light.color.g * light.intensity), light.color.b * light.intensity);
        return (-light.linear +  std::sqrtf(light.linear * light.linear - 4 * light.quadratic * (light.constant - (256.0 / 5.0) * lightMax)))
        / (2 * light.quadratic);  ;
    }

    
    void DeferredRenderer::Init()
    {
        
        s_Buffer.FrameGBuffer = Framebuffer::Create({Application::Get().GetWindow().GetWidth()*2, Application::Get().GetWindow().GetHeight()*2, {FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::RGBA16F, FramebufferTextureFormat::RGBA16F, FramebufferTextureFormat::RGBA16F, FramebufferTextureFormat::DEPTH24STENCIL8}, 1, false});
        s_Buffer.AlbedoSpec = s_Buffer.FrameGBuffer->GetColorAttachmentRendererID(0);
        s_Buffer.Position = s_Buffer.FrameGBuffer->GetColorAttachmentRendererID(1);
        s_Buffer.Normal = s_Buffer.FrameGBuffer->GetColorAttachmentRendererID(2);
        
        s_Buffer.Depth = s_Buffer.FrameGBuffer->GetDepthAttachmentRendererID();
        
        
        s_Buffer.FrameLightBuffer = Framebuffer::Create({Application::Get().GetWindow().GetWidth()*2, Application::Get().GetWindow().GetHeight()*2, {FramebufferTextureFormat::RGBA16F, FramebufferTextureFormat::DEPTH24STENCIL8}, 1, false});
        s_Buffer.Light = s_Buffer.FrameLightBuffer->GetColorAttachmentRendererID();

        s_Buffer.CircleVA = RenderMesh::CreateCircleVAExt(19);
        
        s_Buffer.QuadVA = VertexArray::Create();
        
        s_Buffer.CubeVA = RenderMesh::CreateCubeVA();

        float vertices[4 * 5] = {
            -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
            -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 0.0f, 1.0f, 0.0f 
        };

        Ref<VertexBuffer> vertexBuffer = VertexBuffer::Create(vertices, sizeof(vertices));
        BufferLayout layout = {
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float2, "a_TexCoords" }

        };
        vertexBuffer->SetLayout(layout);
        s_Buffer.QuadVA->AddVertexBuffer(vertexBuffer);

        uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
        Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
        s_Buffer.QuadVA->SetIndexBuffer(indexBuffer);
        s_Buffer.QuadVA->Unbind();

        GraphicsCommand::ToggleBackfaceCulling(false);
        
        s_Buffer.GBufferShader = Shader::Create("EngineContent/Shaders/GBuffer2D.glsl");
        s_Buffer.LightBufferShader = Shader::Create("EngineContent/Shaders/LightBuffer2D.glsl");
        s_Buffer.FinalShader = Shader::Create("EngineContent/Shaders/FinalPass2D.glsl");
        s_Buffer.DecalShader = Shader::Create("EngineContent/Shaders/DecalLight2D.glsl");
        s_Buffer.DepthRenderShader = Shader::Create("EngineContent/Shaders/DepthDrawing2D.glsl");

        
        s_Buffer.DecalQueue = std::vector<Ref<DecalLight>>();
        s_Buffer.RenderQueue = std::vector<RenderItem>();


    }
    void DeferredRenderer::Begin(OrthographicCamera& camera)
    {
        
        s_Buffer.Camera = camera.GetViewProjection();
        s_Buffer.CameraPtr = camera;
        s_Buffer.FrameGBuffer->Bind();
        GraphicsCommand::ToggleBlending(false);
        GraphicsCommand::ToggleDepthTest(true);

        GraphicsCommand::SetClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
        GraphicsCommand::Clear();
        
        s_Buffer.GBufferShader->Bind();
        s_Buffer.GBufferShader->setMat4("u_ViewProjection", s_Buffer.Camera);
        
    }

    void DeferredRenderer::Submit(Ref<RenderMesh>& mesh, glm::vec3 pos, glm::vec3 scale)
    {
        
        s_Buffer.RenderQueue.push_back({mesh, pos, scale});

    }
    
    void DeferredRenderer::BeginLights()
    {
        for(RenderItem item : s_Buffer.RenderQueue)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, item.pos);
            model = glm::scale(model, item.scale);
            s_Buffer.GBufferShader->setMat4("u_Model", model);
            s_Buffer.GBufferShader->setInt("u_AlbedoTexture", 0);
            s_Buffer.GBufferShader->setInt("u_NormalTexture", 1);
            s_Buffer.GBufferShader->setInt("u_SpecularTexture", 2);
            item.mesh->textures[0]->Bind(0);
            item.mesh->textures[1]->Bind(1);
            item.mesh->textures[2]->Bind(2);

            item.mesh->VA->Bind();
            GraphicsCommand::DrawIndexed(item.mesh->VA);
            item.mesh->VA->Unbind();
        }
        s_Buffer.FrameGBuffer->Unbind();
        
        s_Buffer.GBufferShader->Unbind();
        
        s_Buffer.DepthRenderShader->Bind();
        
        
        for(Ref<DecalLight> light : s_Buffer.DecalQueue)
        {
            light->depth->Bind();
            GraphicsCommand::ToggleBlending(false);
            GraphicsCommand::ToggleDepthTest(true);
            GraphicsCommand::SetClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
            GraphicsCommand::Clear();
            s_Buffer.DepthRenderShader->setMat4("u_ViewProjection", light->camera.GetViewProjectionMatrix());
            
            for(RenderItem item : s_Buffer.RenderQueue)
            {
                glm::mat4 model = glm::mat4(1.0f);
                model = glm::translate(model, item.pos);
                model = glm::scale(model, item.scale);
                s_Buffer.DepthRenderShader->setMat4("u_Model", model);
                s_Buffer.DepthRenderShader->setInt("u_AlbedoTexture", 0);
                item.mesh->textures[0]->Bind(0);
                
                item.mesh->VA->Bind();
                GraphicsCommand::DrawIndexed(item.mesh->VA);
                item.mesh->VA->Unbind();
            }
            light->depth->Unbind();
        }
        
        s_Buffer.DepthRenderShader->Unbind();

        
        s_Buffer.FrameLightBuffer->Bind();
        
        GraphicsCommand::SetClearColor({0.0f, 0.0f, 0.0f, 1.0f});
        GraphicsCommand::Clear();
        
        GraphicsCommand::ToggleBlending(true);
        GraphicsCommand::ToggleDepthTest(false);
        
        s_Buffer.LightBufferShader->Bind();
        s_Buffer.LightBufferShader->setMat4("u_ViewProjection", s_Buffer.Camera);
        s_Buffer.LightBufferShader->setInt("gPosition", 0);
        s_Buffer.LightBufferShader->setInt("gNormal", 1);
        
        s_Buffer.CircleVA->Bind();
    }
    
    void DeferredRenderer::DrawPointLight(glm::vec3 pos, glm::vec3 color, float intensity, float constant, float linear, float quadratic)
    {
        PointLight light = PointLight(pos, color, intensity, constant, linear, quadratic);
        
        float radius = CalculateRadius(light);
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, light.position);
        model = glm::scale(model, {radius, radius, 1.0f});
        
        s_Buffer.LightBufferShader->setMat4("u_Model", model);
        
        
        GraphicsCommand::BindTexture(s_Buffer.Position, 0);
        GraphicsCommand::BindTexture(s_Buffer.Normal, 1);
        
        s_Buffer.LightBufferShader->setVec3("u_Light.Position", light.position);
        s_Buffer.LightBufferShader->setVec3("u_Light.Color", light.color);
        s_Buffer.LightBufferShader->setFloat("u_Light.Intensity", light.intensity);
        s_Buffer.LightBufferShader->setFloat("u_Light.Constant", light.constant);
        s_Buffer.LightBufferShader->setFloat("u_Light.Linear", light.linear);
        s_Buffer.LightBufferShader->setFloat("u_Light.Quadratic", light.quadratic);
        
        GraphicsCommand::DrawIndexed(s_Buffer.CircleVA);
        //TODO: Fix this, maybe do a batcher thingie?
    }
    
    
    void DeferredRenderer::DrawDecals()
    {
        s_Buffer.CircleVA->Unbind();
        
        s_Buffer.QuadVA->Bind();

        s_Buffer.DecalShader->Bind();
        
        for(Ref<DecalLight> light : s_Buffer.DecalQueue)
        {
            GraphicsCommand::BindTexture(s_Buffer.Depth, 0);
            GraphicsCommand::BindTexture(light->depth->GetDepthAttachmentRendererID(), 1);
            GraphicsCommand::BindTexture(light->texture->GetID(), 2);
                        
            s_Buffer.DecalShader->setMat4("u_InvView", glm::inverse(s_Buffer.CameraPtr.GetViewMatrix()));
            s_Buffer.DecalShader->setMat4("u_InvProj", glm::inverse(s_Buffer.CameraPtr.GetProjection()));
            s_Buffer.DecalShader->setMat4("u_DecalViewProj", light->camera.GetViewProjectionMatrix());

            s_Buffer.DecalShader->setInt("gDepth", 0);
            s_Buffer.DecalShader->setInt("decalDepth", 1);
            s_Buffer.DecalShader->setInt("u_Decal.Texture", 2);
            
            s_Buffer.DecalShader->setVec3("u_Decal.Color", light->color);
            
            GraphicsCommand::DrawIndexed(s_Buffer.QuadVA);
        }
        s_Buffer.DecalShader->Unbind();
        s_Buffer.QuadVA->Unbind();

    }
    
    void DeferredRenderer::SubmitDecalLight(Ref<DecalLight> decal)
    {
        
        s_Buffer.DecalQueue.push_back(decal);
    }
    
    void DeferredRenderer::End()
    {
        s_Buffer.CircleVA->Unbind();

        s_Buffer.FrameLightBuffer->Unbind();
        
        s_Buffer.FinalShader->Bind();
        s_Buffer.QuadVA->Bind();
        GraphicsCommand::ToggleBlending(false);
        GraphicsCommand::ToggleDepthTest(true);
        
        GraphicsCommand::SetClearColor({0.0f, 0.0f, 0.0f, 1.0f});
        GraphicsCommand::Clear();
        
        s_Buffer.FinalShader->setInt("gLight", 0);
        s_Buffer.FinalShader->setInt("gAlbedoSpec", 1);
        s_Buffer.FinalShader->setFloat("u_Gamma", s_Buffer.Gamma);
        s_Buffer.FinalShader->setVec3("u_Ambient", s_Buffer.Ambient);
        s_Buffer.FinalShader->setFloat("u_Exposure", s_Buffer.Exposure);
        s_Buffer.FinalShader->setFloat("u_Brightness", s_Buffer.BCS.x);
        s_Buffer.FinalShader->setFloat("u_Contrast", s_Buffer.BCS.y);
        s_Buffer.FinalShader->setFloat("u_Saturation", s_Buffer.BCS.z);
        s_Buffer.FinalShader->setFloat("u_BlackPoint", s_Buffer.BWPoint.x);
        s_Buffer.FinalShader->setFloat("u_WhitePoint", s_Buffer.BWPoint.y);
        
        GraphicsCommand::BindTexture(s_Buffer.Light, 0);
        GraphicsCommand::BindTexture(s_Buffer.AlbedoSpec, 1);

        
        GraphicsCommand::DrawIndexed(s_Buffer.QuadVA);
        s_Buffer.QuadVA->Unbind();
        
        s_Buffer.FinalShader->Unbind();
        
        s_Buffer.RenderQueue.clear();
        s_Buffer.DecalQueue.clear();

    }

    void DeferredRenderer::ReloadShaders()
    {
        s_Buffer.GBufferShader->Recompile();
        s_Buffer.LightBufferShader->Recompile();
        s_Buffer.FinalShader->Recompile();
        s_Buffer.DecalShader->Recompile();
        s_Buffer.DepthRenderShader->Recompile();

    }

    uint32_t DeferredRenderer::GetLightID() {return s_Buffer.Light;}
    uint32_t DeferredRenderer::GetPosID() { return s_Buffer.Position;}
    uint32_t DeferredRenderer::GetAlbedoID() { return s_Buffer.AlbedoSpec;}
    uint32_t DeferredRenderer::GetNormalID() {return s_Buffer.Normal;}
    uint32_t DeferredRenderer::GetDepthID() {return s_Buffer.Depth;}

    void DeferredRenderer::SetAmbient(glm::vec3 color) { s_Buffer.Ambient = color; }
    void DeferredRenderer::SetBCS(glm::vec3 bcs) { s_Buffer.BCS = bcs; }
    void DeferredRenderer::SetBWPoint(glm::vec2 bwpoint) {s_Buffer.BWPoint = bwpoint; }

    void DeferredRenderer::SetExposure(float exposure) { s_Buffer.Exposure = exposure; }
    void DeferredRenderer::SetGamma(float gamma) { s_Buffer.Gamma = gamma; }

}
