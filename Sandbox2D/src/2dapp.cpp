#include <Rosewood.h>
#include "imgui.h"


class ExampleLayer : public Rosewood::Layer
{
public:
	unsigned int scrWidth = Rosewood::Application::Get().GetWindow().GetWidth();
	unsigned int scrHeight = Rosewood::Application::Get().GetWindow().GetHeight();
	float lastX = scrWidth / 2.0f;
	float lastY = scrHeight / 2.0f;
	
	Rosewood::Texture myTexture = Rosewood::Texture("C:/dev/Rosewood/assets/container2.png");
	//Rosewood::Shader shader = Rosewood::Shader("C:/dev/Rosewood/assets/shaders/Shader.glsl");
	

	Rosewood::OrthographicCamera camera = Rosewood::OrthographicCamera(0.0f, 0.0f, scrWidth, scrHeight);
	Rosewood::BatchRenderer renderer;

	ExampleLayer()
		: Layer("Example")
	{
		renderer.Init();
		
		
	}

	bool open = true;

	void OnUpdate() override
	{
		renderer.Begin(camera);
		renderer.SetTexture(&myTexture);
		renderer.DrawQuad(glm::vec3(0.0, 0.0), glm::vec2(myTexture.GetWidth(), myTexture.GetHeight()), 0, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec4(1.0f));
		renderer.DrawQuad(glm::vec3(100.0, 100.0), glm::vec2(myTexture.GetWidth()/2, myTexture.GetHeight()/2), 45, glm::vec4(0.0f, 0.0f, 0.5f, 0.5f), glm::vec4(1.0f, 0.0f, 0.0f, 0.5f));
		renderer.End();
	}

	void OnImGuiRender() override
	{
		
		ImGui::Begin("This is 2D Spritebatch System", &open, 0);

		ImGui::Text("FPS:");
		float deltaTime = 1.0f / (float)(Rosewood::Application::GetDeltaTime());
		ImGui::InputFloat("hz", &deltaTime, 0.0f, 0.0f, 5, ImGuiInputTextFlags_None);
		int w = scrWidth;
		int h = scrHeight;
		ImGui::InputInt("px", &w);
		ImGui::InputInt("px", &h);
		
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
	}

	bool OnMouseButtonPressedEvent(Rosewood::MouseButtonPressedEvent& e)
	{
		
		//e.GetMouseButton()
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
		//camera.ProcessMouseScroll( e.GetYOffset());

		return false;
	}

	bool OnKeyPressedEvent(Rosewood::KeyPressedEvent& e)
	{
		int key = e.GetKeyCode();
		if (key == KEY_R)
			Rosewood::Application::Get().GetWindow().LockCursor();
		else if (key == KEY_T)
			Rosewood::Application::Get().GetWindow().UnlockCursor();

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
		glViewport(0, 0, scrWidth, scrHeight);
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