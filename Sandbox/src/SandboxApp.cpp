#include <Rosewood.h>
#include "imgui.h"
#include "FPSCamera.h"
#include "Rosewood/Events/Event.h"

class ExampleLayer : public Rosewood::Layer
{
public:
	Camera camera = Camera();
	ExampleLayer()
		: Layer("Example")
	{
		
	}
	bool open = true;
	void OnUpdate() override
	{
		//RW_INFO(" Ha Ha Pee Pee Updated LOLOLOLOL");
		
	}
	void OnImGuiRender() override
	{
		
		ImGui::Begin("Hello", &open, 0);
		ImGui::Text("Haha yay, it's working!");
		ImGui::Text("FPS:");
		float deltaTime = 1.0 / (Rosewood::Application::GetDeltaTime()+0.00000001);//doesn't make it 0
		ImGui::InputFloat("hz", &deltaTime, 0.0f, 0.0f, 5, ImGuiInputTextFlags_None);
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

	bool OnMouseMovedEvent(Rosewood::MouseMovedEvent& e)
	{
		
		//io.MousePos = ImVec2(e.GetX(), e.GetY());
		//camera.ProcessMouseMovement()
		return false;
	}

	bool OnMouseScrolledEvent(Rosewood::MouseScrolledEvent& e)
	{
		camera.ProcessMouseScroll( e.GetYOffset());

		return false;
	}

	bool OnKeyPressedEvent(Rosewood::KeyPressedEvent& e)
	{
		
		return false;
	}

	bool OnKeyReleasedEvent(Rosewood::KeyReleasedEvent& e)
	{
		//io.KeysDown[e.GetKeyCode()] = false;

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