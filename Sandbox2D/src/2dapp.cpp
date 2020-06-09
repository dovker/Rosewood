#include "Rosewood.h"
#include "Rosewood/EntryPoint.h"
#include "imgui.h"
#include "2DCameraController.h"


class ExampleLayer : public Rosewood::Layer
{
public:
	unsigned int scrWidth = Rosewood::Application::Get().GetWindow().GetWidth();
	unsigned int scrHeight = Rosewood::Application::Get().GetWindow().GetHeight();
	float lastX = scrWidth / 2.0f;
	float lastY = scrHeight / 2.0f;
	
	Rosewood::Texture myTexture = Rosewood::Texture("/Users/dovydas/Documents/GitHub/Rosewood/assets/container.jpg");

	

	//Rosewood::OrthographicCamera camera = Rosewood::OrthographicCamera(0.0f, 0.0f, scrWidth, scrHeight);
	//Camera camera = Camera({ scrWidth, scrHeight });
	Camera camera = Camera(glm::vec2( (float)scrWidth, (float)scrHeight));
	
	ExampleLayer()
		: Layer("Example")
	{
		Rosewood::BatchRenderer::Init();
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		
		//ADD BLENDING
	}

	bool open = true;

	void OnUpdate() override
	{
		camera.ProcessKeyboard(Rosewood::Application::GetDeltaTime());

		Rosewood::BatchRenderer::ResetStats();

		Rosewood::BatchRenderer::Begin(camera.GetCamera());

		Rosewood::BatchRenderer::DrawQuad(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(myTexture.GetWidth(), myTexture.GetHeight()), myTexture, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

		for (int i = 0; i < 100; i++)
		{
			for (int j = 0; j < 100; j++)
			{
                Rosewood::BatchRenderer::DrawQuad(glm::vec3(i * 10, j*10, 0.0f), glm::vec2(10.0f), glm::vec4((float)i / 100.0f, (float)j / 100.0f, glm::sin(Rosewood::Application::GetTime()), 0.6f));
			}
		}

		Rosewood::BatchRenderer::End();
	}

	void OnImGuiRender() override
	{
		auto stats = Rosewood::BatchRenderer::GetStats();
		ImGui::Begin("This is 2D Spritebatch System", &open, 0);
		ImGui::Text("Camera Pos: %f, %f, %f", camera.GetCamera().GetPosition().x, camera.GetCamera().GetPosition().y, camera.GetCamera().GetPosition().z);
        ImGui::Text("Batch stats: %i, %i", stats.DrawCount, stats.QuadCount);
		ImGui::Text("FPS:");
		float deltaTime = 1.0f / (float)(Rosewood::Application::GetDeltaTime());
		ImGui::InputFloat("hz", &deltaTime, 0.0f, 0.0f, 5, ImGuiInputTextFlags_None);
		int w = scrWidth;
		int h = scrHeight;
		ImGui::InputInt("px", &w);
        ImGui::InputInt("px", &h);
        ImGui::Image((ImTextureID)myTexture.GetID(), ImVec2(500, 500));
		
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
		camera.ProcessMouseScroll( e.GetYOffset());

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
		camera.ProcessScreenResize(glm::vec2(scrWidth, scrHeight));
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
		Rosewood::BatchRenderer::Shutdown();
	}
};

Rosewood::Application* Rosewood::CreateApplication()
{

	return new Sandbox();
}
