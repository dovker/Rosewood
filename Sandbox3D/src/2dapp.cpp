#include "Rosewood.h"
#include "Rosewood/Core/EntryPoint.h"
#include "imgui.h"

const std::string Rosewood::FileSystem::ProjectRoot = "../../../Sandbox3D/";


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
    
    Rosewood::Ref<Rosewood::Sound> sound;
    
    Rosewood::EditorCamera camera = Rosewood::EditorCamera(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
        
    bool open = true;
    
    float mouseX = 0.0f;
    float mouseY = 0.0f;
	
	ExampleLayer()
		: Layer("Example")
	{
        model = Rosewood::Model::Create("Content/globe.fbx");

        Rosewood::Renderer::Init();
        
	}

	
    void OnUpdate(Rosewood::Timestep timestep) override
	{
        
        camera.OnUpdate(timestep);
        
        Rosewood::Renderer::Begin(camera);
        glm::mat4 modelMat = glm::mat4(1.0f);
        modelMat = glm::scale(modelMat, {0.1, 0.1, 0.1});
        modelMat = glm::translate(modelMat, {0.0f, 0.0f, -100.0f});
        Rosewood::Renderer::Submit(model, modelMat);
        Rosewood::Renderer::End();


	}



	void OnImGuiRender() override
	{
		ImGui::Begin("This is 3D Renderer", &open, 0);

		        
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

    }
};

Rosewood::Application* Rosewood::CreateApplication()
{

	return new Sandbox();
}


