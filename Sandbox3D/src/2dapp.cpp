#include "Rosewood.h"
#include "Rosewood/EntryPoint.h"
#include "imgui.h"


class ExampleLayer : public Rosewood::Layer
{
public:
	unsigned int scrWidth = Rosewood::Application::Get().GetWindow().GetWidth();
	unsigned int scrHeight = Rosewood::Application::Get().GetWindow().GetHeight();
	float lastX = scrWidth / 2.0f;
	float lastY = scrHeight / 2.0f;
	
    Rosewood::Ref<Rosewood::Texture> texture;
    Rosewood::Ref<Rosewood::Texture> fontTexture;
    
    Rosewood::Ref<Rosewood::Model> model;
    
    Rosewood::AssetManager assetManager;
    Rosewood::Ref<Rosewood::Sound> sound;
    
    Rosewood::EditorCamera camera = Rosewood::EditorCamera(45.0f, 16.0f/9.0f, 0.00001f, 1000000.0f);
        
    bool open = true;
    
    float mouseX = 0.0f;
    float mouseY = 0.0f;
	
	ExampleLayer()
		: Layer("Example")
	{
        Rosewood::Renderer::Init();
        model = Rosewood::Model::Create("Content/nanosuit/nanosuit.mtl");
        
	}

	
    void OnUpdate() override
	{
        {
            Rosewood::GraphicsCommand::SetClearColor(glm::vec4(0.1f, 0.12f, 0.1f, 1.0f));
            Rosewood::GraphicsCommand::Clear();
        }
        camera.OnUpdate(Rosewood::Application::GetDeltaTime());
        Rosewood::Renderer::Begin(camera);
        glm::mat4 modelMat = glm::mat4(1.0f);
        Rosewood::Renderer::Submit(model, modelMat);
        Rosewood::Renderer::End();


	}



	void OnImGuiRender() override
	{
		ImGui::Begin("This is 3D Renderer", &open, 0);

		ImGui::Text("FPS:");
		float deltaTime = 1.0f / (float)(Rosewood::Application::GetDeltaTime());
		ImGui::InputFloat("hz", &deltaTime);
        
        ImGui::Separator();

        
        ImGui::Separator();
        
        
		
		ImGui::End();
	}
	void OnEvent(Rosewood::Event& event) override
	{
		Rosewood::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Rosewood::MouseButtonPressedEvent>(RW_BIND_EVENT_FN(ExampleLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<Rosewood::MouseButtonReleasedEvent>(RW_BIND_EVENT_FN(ExampleLayer::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<Rosewood::MouseMovedEvent>(RW_BIND_EVENT_FN(ExampleLayer::OnMouseMovedEvent));
		dispatcher.Dispatch<Rosewood::MouseScrolledEvent>(RW_BIND_EVENT_FN(ExampleLayer::OnMouseScrolledEvent));
		dispatcher.Dispatch<Rosewood::KeyPressedEvent>(RW_BIND_EVENT_FN(ExampleLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<Rosewood::KeyReleasedEvent>(RW_BIND_EVENT_FN(ExampleLayer::OnKeyReleasedEvent));
		dispatcher.Dispatch<Rosewood::WindowResizeEvent>(RW_BIND_EVENT_FN(ExampleLayer::OnWindowResizeEvent));
        camera.OnEvent(event);
	}

	bool OnMouseButtonPressedEvent(Rosewood::MouseButtonPressedEvent& e)
	{
        
		return false;
	}

	bool OnMouseButtonReleasedEvent(Rosewood::MouseButtonReleasedEvent& e)
	{
		

		return false;
	}

	bool firstMouse = true;

	bool OnMouseMovedEvent(Rosewood::MouseMovedEvent& e)
	{
		
		return false;
	}

	bool OnMouseScrolledEvent(Rosewood::MouseScrolledEvent& e)
	{
		
		return false;
	}

	bool OnKeyPressedEvent(Rosewood::KeyPressedEvent& e)
	{
		
		return false;
	}

	bool OnKeyReleasedEvent(Rosewood::KeyReleasedEvent& e)
	{

		return false;
	}
	bool OnWindowResizeEvent(Rosewood::WindowResizeEvent& e)
	{
		scrWidth = e.GetWidth();
		scrHeight = e.GetHeight();
        Rosewood::GraphicsCommand::SetViewport(0, 0, scrWidth, scrHeight);
		return false;
	}
};

class Sandbox : public Rosewood::Application
{
public:

	Sandbox()
	{
		PushLayer(new ExampleLayer());  
	}

	~Sandbox()
	{
		//Rosewood::DeferredRenderer::Shutdown();
        Rosewood::BatchRenderer::Shutdown();

	}
};

Rosewood::Application* Rosewood::CreateApplication()
{

	return new Sandbox();
}


