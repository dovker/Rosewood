#include <Rosewood.h>
#include "imgui.h"
#include "FPSCamera.h"

#include "Map.h"
#include "Chunk.h"

class ExampleLayer : public Rosewood::Layer
{
public:
	unsigned int scrWidth = Rosewood::Application::Get().GetWindow().GetWidth();
	unsigned int scrHeight = Rosewood::Application::Get().GetWindow().GetHeight();
	float lastX = scrWidth / 2.0f;
	float lastY = scrHeight / 2.0f;
	/*
	std::vector<Rosewood::Vertex> vertices{
		// positions          // normals           // texture coords
		Rosewood::Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f),  glm::vec2(0.0f, 0.0f)),
		Rosewood::Vertex(glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f),  glm::vec2(1.0f, 0.0f)),
		Rosewood::Vertex(glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f),  glm::vec2(1.0f, 1.0f)),
		Rosewood::Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  0.0f, -1.0f),  glm::vec2(0.0f, 1.0f)),
		Rosewood::Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f),  glm::vec2(0.0f, 0.0f)),
		Rosewood::Vertex(glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f),  glm::vec2(1.0f, 0.0f)),
		Rosewood::Vertex(glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f),  glm::vec2(1.0f, 1.0f)),
		Rosewood::Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  0.0f,  1.0f),  glm::vec2(0.0f, 1.0f)),
		Rosewood::Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f),  glm::vec2(1.0f, 0.0f)),
		Rosewood::Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f),  glm::vec2(1.0f, 1.0f)),
		Rosewood::Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-1.0f,  0.0f,  0.0f),  glm::vec2(0.0f, 1.0f)),
		Rosewood::Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3(-1.0f,  0.0f,  0.0f),  glm::vec2(0.0f, 0.0f)),
		Rosewood::Vertex(glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 1.0f,  0.0f,  0.0f),  glm::vec2(1.0f, 0.0f)),
		Rosewood::Vertex(glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 1.0f,  0.0f,  0.0f),  glm::vec2(1.0f, 1.0f)),
		Rosewood::Vertex(glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 1.0f,  0.0f,  0.0f),  glm::vec2(0.0f, 1.0f)),
		Rosewood::Vertex(glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 1.0f,  0.0f,  0.0f),  glm::vec2(0.0f, 0.0f)),
		Rosewood::Vertex(glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3( 0.0f, -1.0f,  0.0f),  glm::vec2(0.0f, 1.0f)),
		Rosewood::Vertex(glm::vec3( 0.5f, -0.5f, -0.5f), glm::vec3( 0.0f, -1.0f,  0.0f),  glm::vec2(1.0f, 1.0f)),
		Rosewood::Vertex(glm::vec3( 0.5f, -0.5f,  0.5f), glm::vec3( 0.0f, -1.0f,  0.0f),  glm::vec2(1.0f, 0.0f)),
		Rosewood::Vertex(glm::vec3(-0.5f, -0.5f,  0.5f), glm::vec3( 0.0f, -1.0f,  0.0f),  glm::vec2(0.0f, 0.0f)),
		Rosewood::Vertex(glm::vec3(-0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  1.0f,  0.0f),  glm::vec2(0.0f, 1.0f)),
		Rosewood::Vertex(glm::vec3( 0.5f,  0.5f, -0.5f), glm::vec3( 0.0f,  1.0f,  0.0f),  glm::vec2(1.0f, 1.0f)),
		Rosewood::Vertex(glm::vec3( 0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  1.0f,  0.0f),  glm::vec2(1.0f, 0.0f)),
		Rosewood::Vertex(glm::vec3(-0.5f,  0.5f,  0.5f), glm::vec3( 0.0f,  1.0f,  0.0f),  glm::vec2(0.0f, 0.0f)),
	};

	std::vector<unsigned int> indexes
	{
		1, 2, 3,
		3, 4, 1,

		5, 6, 7,
		7, 8, 5,

		9, 10, 11,
		11, 12, 9,

		13, 14, 15,
		15, 16, 13,

		17, 18, 19,
		19, 20, 17,

		21, 22, 23,
		23, 24, 21
	};
	*/
	std::vector<Rosewood::Vertex> vertices{
	};

	std::vector<unsigned int> indexes
	{
	};
	
	

	Rosewood::Texture myTexture = Rosewood::Texture("C:/dev/Rosewood/assets/container2.png");
	Rosewood::Shader shader = Rosewood::Shader("C:/dev/Rosewood/assets/shaders/Shader.glsl");
	Rosewood::Mesh mesh; 
	Map map = Map(8, 8);

	Camera camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));

	ExampleLayer()
		: Layer("Example")
	{
		
		//RW_TRACE("Map created successfully. Texture path: {0}", map.chunks[0]->mesh.texture->GetHeight());
		mesh = Rosewood::Mesh(&myTexture);
		
		mesh.AddQuad(glm::vec3(0.0f, 0.0f, 0.0f), Rosewood::Orientation::Down, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f));
		mesh.AddQuad(glm::vec3(0.0f, 0.0f, 0.0f), Rosewood::Orientation::Up, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f));
		mesh.AddQuad(glm::vec3(0.0f, 0.0f, 0.0f), Rosewood::Orientation::Left, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f));
		mesh.AddQuad(glm::vec3(0.0f, 0.0f, 0.0f), Rosewood::Orientation::Right, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f));
		mesh.AddQuad(glm::vec3(0.0f, 0.0f, 0.0f), Rosewood::Orientation::Back, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f));
		mesh.AddQuad(glm::vec3(0.0f, 0.0f, 0.0f), Rosewood::Orientation::Front, glm::vec2(0.0f, 0.0f), glm::vec2(1.0f, 1.0f));
		mesh.SetupMesh();
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//glEnable(GL_CULL_FACE);
		//glCullFace(GL_BACK);
		//glFrontFace(GL_CW);
		 // PPPPPAAAATTTTAAAAIIIISSSSYYYYTTTTIIII
		
	}

	bool open = true;

	void OnUpdate() override
	{
		camera.ProcessKeyboard(Rosewood::Application::GetDeltaTime());

		glm::mat4 view = glm::mat4(1.0f);
		view = glm::lookAt(camera.Position, camera.Position + camera.Front, camera.Up);

		glm::mat4 model = glm::mat4(1.0f);
		//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

		glm::mat4 projection;
		projection = glm::perspective(glm::radians(camera.Zoom), (float)scrWidth / (float)scrHeight, 0.1f, 1000.0f);

		//myTexture.Bind(0);

		shader.use();
		shader.setMat4("model", model);
		shader.setMat4("view", view);
		shader.setMat4("projection", projection);
		
		
		mesh.Draw(shader);
		map.Draw(&myTexture);

		//map.chunks[0]->mesh.Draw(shader);
	}

	void OnImGuiRender() override
	{
		float campos[3] = {camera.Position.x, camera.Position.y, camera.Position.z};
		ImGui::Begin("Hello", &open, 0);
		ImGui::SliderFloat3("Camera pos:", campos, 0.0f, 1000.0f);
		ImGui::Text("Haha yay, it's working!");
		ImGui::Text("FPS:");
		float deltaTime = 1.0f / (float)(Rosewood::Application::GetDeltaTime()+0.00000001f);//doesn't make it 0
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
		if (firstMouse)
		{
			lastX = e.GetX();
			lastY = e.GetY();
			firstMouse = false;
		}

		float xoffset = e.GetX() - lastX;
		float yoffset = lastY - e.GetY(); // reversed since y-coordinates go from bottom to top
		lastX = e.GetX();
		lastY = e.GetY();

		camera.ProcessMouseMovement(xoffset, yoffset);
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
		int key = e.GetKeyCode();
		if (key == KEY_R)
			Rosewood::Application::Get().GetWindow().LockCursor();
		else if (key == KEY_T)
			Rosewood::Application::Get().GetWindow().UnlockCursor();

		return false;
	}

	bool OnKeyReleasedEvent(Rosewood::KeyReleasedEvent& e)
	{
		//io.KeysDown[e.GetKeyCode()] = false;

		return false;
	}
	bool OnWindowResizeEvent(Rosewood::WindowResizeEvent& e)
	{
		//io.KeysDown[e.GetKeyCode()] = false;
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