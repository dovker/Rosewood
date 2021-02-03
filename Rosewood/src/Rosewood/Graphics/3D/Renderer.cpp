#include "rwpch.h"

#include "Rosewood/Graphics/Graphics.h"
#include "Rosewood/Application.h"
#include "Renderer.h"


namespace Rosewood
{

    struct GBuffer
    {
        Ref<Framebuffer> FrameGBuffer;
        
        uint32_t Position;
        uint32_t Depth;

        uint32_t Albedo;
        uint32_t Normal;
        uint32_t MetalicRoughAO;
        uint32_t Emissive;
        
        Ref<VertexArray> SphereVA;
        Ref<VertexArray> QuadVA;
        
        Ref<Shader> GBufferShader;
        Ref<Shader> FinalShader;
        
        glm::vec3 Ambient;
        float Exposure;
        float Gamma;
        glm::vec3 BCS; //Brightness, contrast, Saturation
        glm::vec2 BWPoint; //Black point and White point

        glm::mat4 Camera;
        EditorCamera CameraPtr;
    };

    static GBuffer s_Buffer;

//    float CalculateRadius(const PointLight &light)
//    {
//        float lightMax  = std::fmaxf(std::fmaxf(light.color.r * light.intensity, light.color.g * light.intensity), light.color.b * light.intensity);
//        return (-light.linear +  std::sqrtf(light.linear * light.linear - 4 * light.quadratic * (light.constant - (256.0 / 5.0) * lightMax)))
//        / (2 * light.quadratic);  ;
//    }


    void Renderer::Init()
    {
        
        s_Buffer.FrameGBuffer = Framebuffer::Create({Application::Get().GetWindow().GetWidth()*2, Application::Get().GetWindow().GetHeight()*2, {FramebufferTextureFormat::RGB16F, FramebufferTextureFormat::RGB8, FramebufferTextureFormat::RGB16F, FramebufferTextureFormat::RGB8, FramebufferTextureFormat::RGB16F, FramebufferTextureFormat::DEPTH24STENCIL8}, 1, false});
        s_Buffer.Position = s_Buffer.FrameGBuffer->GetColorAttachmentRendererID(0);
        s_Buffer.Albedo = s_Buffer.FrameGBuffer->GetColorAttachmentRendererID(1); //DO SOMETHING ABOUT CHANNELS
        s_Buffer.Normal = s_Buffer.FrameGBuffer->GetColorAttachmentRendererID(2);
        s_Buffer.MetalicRoughAO = s_Buffer.FrameGBuffer->GetColorAttachmentRendererID(3);
        s_Buffer.Emissive = s_Buffer.FrameGBuffer->GetColorAttachmentRendererID(4);

        s_Buffer.Depth = s_Buffer.FrameGBuffer->GetDepthAttachmentRendererID();
        
        s_Buffer.QuadVA = VertexArray::Create();


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

        uint32_t indices[6] = { 0, 2, 1, 2, 0, 3 };
        Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
        s_Buffer.QuadVA->SetIndexBuffer(indexBuffer);
        s_Buffer.QuadVA->Unbind();

        
        
        s_Buffer.GBufferShader = Shader::Create("EngineContent/Shaders/GBuffer.glsl");
        s_Buffer.FinalShader = Shader::Create("EngineContent/Shaders/FinalPass.glsl");
    }
    void Renderer::Begin(EditorCamera& camera)
    {
        
        s_Buffer.Camera = camera.GetViewProjection();
        s_Buffer.CameraPtr = camera;
        s_Buffer.FrameGBuffer->Bind();
        //GraphicsCommand::ToggleBlending(false);
        //GraphicsCommand::ToggleDepthTest(true);
        
        GraphicsCommand::ToggleBackfaceCulling(true);

        GraphicsCommand::SetClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
        GraphicsCommand::Clear();
        
        s_Buffer.GBufferShader->Bind();
        s_Buffer.GBufferShader->setMat4("u_ViewProjection", s_Buffer.Camera);
        
    }

    void Renderer::Submit(Ref<Model>& model, glm::mat4 transform)
    {
        model->SetShader(s_Buffer.GBufferShader);
        model->BindMaterial();
        s_Buffer.GBufferShader->setMat4("u_Model", transform);

        for(auto& mesh : model->GetMeshes())
        {
            if(mesh->HasTextures())
                model->BindMeshTextures(mesh);
            
            mesh->VA->Bind();
            GraphicsCommand::DrawIndexed(mesh->VA);
            mesh->VA->Unbind();
        }
    }
    void Renderer::Submit(Ref<Mesh>& mesh, glm::mat4 transform)
    {
        s_Buffer.GBufferShader->setMat4("u_Model", transform);

        mesh->VA->Bind();
        GraphicsCommand::DrawIndexed(mesh->VA);
        mesh->VA->Unbind();
        
    }
    

    void Renderer::End()
    {
        /* Per Each Mesh Draw GBuffer*/
        /*
         Per each shader
            Per each mesh
                Compute Lighting
                
         */
        s_Buffer.GBufferShader->Unbind();
        s_Buffer.FrameGBuffer->Unbind();
        
        s_Buffer.FinalShader->Bind();
        //GraphicsCommand::ToggleBlending(false);
        //GraphicsCommand::ToggleDepthTest(true);
        
        GraphicsCommand::SetClearColor({0.0f, 0.0f, 0.0f, 1.0f});
        GraphicsCommand::Clear();
        
        s_Buffer.FinalShader->setInt("uBuffer", 0);
        
        GraphicsCommand::BindTexture(s_Buffer.Albedo, 0);
        
        s_Buffer.QuadVA->Bind();
        GraphicsCommand::DrawIndexed(s_Buffer.QuadVA);
        s_Buffer.QuadVA->Unbind();
        
        s_Buffer.FinalShader->Unbind();
        
//        s_Buffer.RenderQueue.clear();
//        s_Buffer.DecalQueue.clear();

    }
}
