#include "rwpch.h"

#include "DeferredRenderer.h"
#include "Graphics.h"
#include "Rosewood/Application.h"

#include "FrameBuffer.h"
#include "Shader.h"

namespace Rosewood
{
    struct PointLight
    {
        glm::vec3 position;
        
        glm::vec3 color;
        
        float constant;
        float linear;
        float quadratic;
        
        PointLight(glm::vec3 pos, glm::vec3 col, float cons, float lin, float quadr)
        : position(pos), color(col), constant(cons), linear(lin), quadratic(quadr)
        {}
    };

    struct GBuffer
    {
        Ref<Framebuffer> FrameGBuffer;
        
        Ref<Framebuffer> FrameLightBuffer;

        
        Ref<Shader> GBufferShader;
        Ref<Shader> LightBufferShader;
        Ref<Shader> FinalShader;

        uint32_t AlbedoSpec;
        uint32_t Position;
        uint32_t Normal;
        uint32_t Light;
        
        Ref<VertexArray> QuadVA;
        
        Ref<VertexArray> CircleVA;
        
        glm::vec4 Ambient;
        
        std::vector<PointLight> Lights;
        glm::mat4 Camera;

    };

    static GBuffer s_Buffer;

    float CalculateRadius(const PointLight &light)
    {
        float lightMax  = std::fmaxf(std::fmaxf(light.color.r, light.color.g), light.color.b);
        return (-light.linear +  std::sqrtf(light.linear * light.linear - 4 * light.quadratic * (light.constant - (256.0 / 5.0) * lightMax)))
        / (2 * light.quadratic);  ;
    }

    Ref<VertexArray> CreateCircleVA(int segments)
    {
        uint32_t vertexSegments = segments + 2;
        uint32_t numberOfVertices = 3*vertexSegments;
        
        float twoPi = glm::two_pi<float>();
        
        std::vector<uint32_t> indices(vertexSegments*3);
        
		std::vector<float> circleVertices(numberOfVertices);
        
        uint32_t currentIndex = 0;
        uint32_t currentVIndex = 3;

        
        circleVertices[0] = 0.0f;
        circleVertices[1] = 0.0f;
        circleVertices[2] = 0.0f;
        
        for (int i = 1; i < numberOfVertices/3; i++)
        {
            circleVertices[currentVIndex] = cos(i*twoPi / segments);
            circleVertices[currentVIndex + 1] = sin(i*twoPi / segments);
            circleVertices[currentVIndex + 2] = 0.0f;
            
            indices[currentIndex] = 0;
            indices[currentIndex + 1] = i-1;
            indices[currentIndex + 2] = i;
            currentIndex+=3;
            currentVIndex += 3;
        }
        Ref<VertexArray> VA = VertexArray::Create();
        
        Ref<VertexBuffer> VB = VertexBuffer::Create(circleVertices.data(), sizeof(circleVertices));
        BufferLayout layout = {
            { ShaderDataType::Float3, "a_Position" }
        };
        VB->SetLayout(layout);
        VA->AddVertexBuffer(VB);

        Ref<IndexBuffer> IB = IndexBuffer::Create(indices.data(), sizeof(indices) / sizeof(uint32_t));
        VA->SetIndexBuffer(IB);
        
        return VA;
    }
    Ref<VertexArray> CreateCircleVAExt(int segments)
    {
        uint32_t vertexSegments = segments + 2;
        uint32_t numberOfVertices = 5*vertexSegments;
        
        float twoPi = glm::two_pi<float>();
        
		std::vector<uint32_t> indices(vertexSegments*3);
        
		std::vector<float> circleVertices(numberOfVertices);
        
        uint32_t currentIndex = 0;
        uint32_t currentVIndex = 5;

        
        circleVertices[0] = 0.0f;
        circleVertices[1] = 0.0f;
        circleVertices[2] = 0.0f;
        circleVertices[3] = 0.0f;
        circleVertices[4] = 0.0f;

        
        for (int i = 1; i < numberOfVertices/5; i++)
        {
            circleVertices[currentVIndex] = cos(i*twoPi / segments);
            circleVertices[currentVIndex + 1] = sin(i*twoPi / segments);
            circleVertices[currentVIndex + 2] = 0.0f;
            circleVertices[currentVIndex + 3] = circleVertices[currentVIndex];
            circleVertices[currentVIndex + 4] = circleVertices[currentVIndex + 1];
            indices[currentIndex] = 0;
            indices[currentIndex + 1] = i-1;
            indices[currentIndex + 2] = i;
            currentIndex+=3;
            currentVIndex += 5;
        }
        Ref<VertexArray> VA = VertexArray::Create();
        
        Ref<VertexBuffer> VB = VertexBuffer::Create(circleVertices.data(), sizeof(circleVertices));
        BufferLayout layout = {
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float2, "a_TexCoords" }
        };
        VB->SetLayout(layout);
        VA->AddVertexBuffer(VB);

        Ref<IndexBuffer> IB = IndexBuffer::Create(indices.data(), sizeof(indices) / sizeof(uint32_t));
        VA->SetIndexBuffer(IB);
        VA->Unbind();
        return VA;
    }
    void DeferredRenderer::Init()
    {
        s_Buffer.FrameGBuffer = Framebuffer::Create({Application::Get().GetWindow().GetWidth()*2, Application::Get().GetWindow().GetHeight()*2, 3});
        s_Buffer.AlbedoSpec = s_Buffer.FrameGBuffer->GetColorAttachmentRendererID(0);
        std::cout<<s_Buffer.AlbedoSpec;
        s_Buffer.Position = s_Buffer.FrameGBuffer->GetColorAttachmentRendererID(1);
        std::cout<<s_Buffer.Position;
        s_Buffer.Normal = s_Buffer.FrameGBuffer->GetColorAttachmentRendererID(2);
        std::cout<<s_Buffer.Normal;

        
        
        s_Buffer.FrameLightBuffer = Framebuffer::Create({Application::Get().GetWindow().GetWidth()*2, Application::Get().GetWindow().GetHeight()*2});
        s_Buffer.Light = s_Buffer.FrameLightBuffer->GetColorAttachmentRendererID();
        //TODO: FIX VA generation
        s_Buffer.CircleVA = CreateCircleVAExt(19);

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

        uint32_t indices[6] = { 0, 1, 2, 2, 3, 0 };
        Ref<IndexBuffer> indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
        s_Buffer.QuadVA->SetIndexBuffer(indexBuffer);
        s_Buffer.QuadVA->Unbind();

        
        
        s_Buffer.GBufferShader = Shader::Create("EngineContent/Shaders/GBuffer.glsl");
        s_Buffer.LightBufferShader = Shader::Create("EngineContent/Shaders/LightBuffer.glsl");
        s_Buffer.FinalShader = Shader::Create("EngineContent/Shaders/FinalPass.glsl");
//

    }
    void DeferredRenderer::Begin(glm::mat4 camera)
    {
        s_Buffer.Camera = camera;
        s_Buffer.FrameGBuffer->Bind();
        GraphicsCommand::SetClearColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
        GraphicsCommand::Clear();
        
        s_Buffer.GBufferShader->Bind();
        s_Buffer.GBufferShader->setMat4("u_ViewProjection", camera);
        
    }
    void DeferredRenderer::Submit(Ref<RenderMesh> mesh, glm::vec3 pos, glm::vec3 scale)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, pos);
        model = glm::scale(model, scale);
        s_Buffer.GBufferShader->setMat4("u_Model", model);
        s_Buffer.GBufferShader->setInt("u_AlbedoTexture", 0);
        s_Buffer.GBufferShader->setInt("u_NormalTexture", 1);
        s_Buffer.GBufferShader->setInt("u_SpecularTexture", 2);
        mesh->textures[0]->Bind(0);
        mesh->textures[1]->Bind(1);
        mesh->textures[2]->Bind(2);

//        mesh->VA->Bind();
//        GraphicsCommand::DrawIndexed(mesh->VA);
//        mesh->VA->Unbind();
        s_Buffer.QuadVA->Bind();
        GraphicsCommand::DrawIndexed(s_Buffer.QuadVA);
        s_Buffer.QuadVA->Unbind();
    }
    void DeferredRenderer::End()
    {
        //RW_CORE_TRACE("GBuffer done");
        s_Buffer.FrameGBuffer->Unbind();
        
        
        //Light Pass
        s_Buffer.FrameLightBuffer->Bind();
        GraphicsCommand::SetClearColor({0.0f, 0.0f, 0.0f, 1.0f});
        GraphicsCommand::Clear();
        
        s_Buffer.LightBufferShader->Bind();
        
        s_Buffer.LightBufferShader->setMat4("u_ViewProjection", s_Buffer.Camera);
        
        s_Buffer.LightBufferShader->setInt("gPosition", 0);
        s_Buffer.LightBufferShader->setInt("gNormal", 1);
        GraphicsCommand::BindTexture(s_Buffer.Position, 0);
        GraphicsCommand::BindTexture(s_Buffer.Normal, 1);

        
//        s_Buffer.CircleVA->Bind();
        s_Buffer.QuadVA->Bind();
        for (struct PointLight light : s_Buffer.Lights)
        {
            float radius = CalculateRadius(light);
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, light.position);
            model = glm::scale(model, {radius, radius, 1.0f});
            s_Buffer.LightBufferShader->setMat4("u_Model", model);
        
            s_Buffer.LightBufferShader->setVec3("u_Light.Position", light.position);
            s_Buffer.LightBufferShader->setVec3("u_Light.Color", light.color);
            s_Buffer.LightBufferShader->setFloat("u_Light.Constant", light.constant);
            s_Buffer.LightBufferShader->setFloat("u_Light.Linear", light.linear);
            s_Buffer.LightBufferShader->setFloat("u_Light.Quadratic", light.quadratic);
            
            //GraphicsCommand::DrawIndexed(s_Buffer.CircleVA);
            GraphicsCommand::DrawIndexed(s_Buffer.QuadVA);
        }
        //RW_CORE_TRACE("light pass done");
        
        s_Buffer.FrameLightBuffer->Unbind();
        
        
        
        s_Buffer.FinalShader->Bind();
        
        s_Buffer.FinalShader->setInt("u_Image", 0);

        //s_Buffer.FinalShader->setInt("gLight", s_Buffer.Light);
        GraphicsCommand::BindTexture(s_Buffer.Light, 0);
                //RW_CORE_TRACE("Last pass done");
        s_Buffer.QuadVA->Bind();
        GraphicsCommand::DrawIndexed(s_Buffer.QuadVA);
        s_Buffer.QuadVA->Unbind();


//
//        //Final Pass
//        s_Buffer.FinalShader->Bind();
//
//        s_Buffer.FinalShader->setInt("gLight", s_Buffer.Light);
//        s_Buffer.FinalShader->setInt("gAlbedoSpec", s_Buffer.AlbedoSpec);
//        s_Buffer.FinalShader->setVec3("u_Ambient", s_Buffer.Ambient);
//        //RW_CORE_TRACE("Last pass done");
//        //GraphicsCommand::DrawIndexed(s_Buffer.QuadVA);

    }

    void DeferredRenderer::PointLight(glm::vec2 pos, glm::vec3 color, float constant, float linear, float quadratic)
    {
        s_Buffer.Lights.push_back({{pos.x, pos.y, 1.0f-0.00000001}, color, constant, linear, quadratic});
    }

    uint32_t DeferredRenderer::GetLightID() {return s_Buffer.Light;}
    uint32_t DeferredRenderer::GetPosID() { return s_Buffer.Position;}
    uint32_t DeferredRenderer::GetAlbedoID() { return s_Buffer.AlbedoSpec;}
    uint32_t DeferredRenderer::GetNormalID() {return s_Buffer.Normal;}
}
