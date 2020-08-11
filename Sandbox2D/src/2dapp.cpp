#include "Rosewood.h"
#include "imgui.h"
#include "2DCameraController.h"


class ExampleLayer : public Rosewood::Layer
{
public:
	unsigned int scrWidth = Rosewood::Application::Get().GetWindow().GetWidth();
	unsigned int scrHeight = Rosewood::Application::Get().GetWindow().GetHeight();
	float lastX = scrWidth / 2.0f;
	float lastY = scrHeight / 2.0f;
	
    Rosewood::Ref<Rosewood::Texture> texture;
    Rosewood::Ref<Rosewood::Texture> fontTexture;

    
    Rosewood::Ref<Rosewood::SpriteFont> font;
    
    Rosewood::AssetManager assetManager;
    Rosewood::Ref<Rosewood::VertexArray> m_VertexArray;
    Rosewood::Ref<Rosewood::Framebuffer> m_Framebuffer;
    Rosewood::Ref<Rosewood::Sound> sound;
    
    //Rosewood::Sound sound = Rosewood::Audio::LoadAudioSource("/Users/dovydas/Documents/GitHub/Rosewood/assets/sound.mp3");
    Rosewood::Ref<Rosewood::RenderMesh> mesh;

    Camera camera = Camera(glm::vec2( (float)scrWidth, (float)scrHeight));
    
	
	ExampleLayer()
		: Layer("Example")
	{
        Rosewood::Ref<Rosewood::Texture> albedo = assetManager.Load<Rosewood::Texture>("Content/Deferred_Albedo.png", "Deferred_Albedo");
        Rosewood::Ref<Rosewood::Texture> normal = assetManager.Load<Rosewood::Texture>("Content/normals.png", "Deferred_Normal");
        Rosewood::Ref<Rosewood::Texture> spec = assetManager.Load<Rosewood::Texture>("Content/Deferred_Specular.png", "Deferred_Specular");


        
        assetManager.Load<Rosewood::Sound>("Content/sound.mp3", "Sound");
        assetManager.Load<Rosewood::Texture>("Content/Chroma.png", "Sprite_Font");
        
        mesh = Rosewood::RenderMesh::Create(
        std::vector<float>{-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
                           -1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
                            1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
                            1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f},
        std::vector<uint32_t>{ 0, 1, 2, 2, 3, 0 },
        std::vector<Rosewood::Ref<Rosewood::Texture>>{albedo, normal, spec});

        sound = assetManager.Get<Rosewood::Sound>("Sound");
        fontTexture = assetManager.Get<Rosewood::Texture>("Sprite_Font");
        
        font = Rosewood::SpriteFont::Create(fontTexture, "!\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ ", 9, 9);

        Rosewood::DeferredRenderer::Init();
        

	}

	bool open = true;
    std::string text = "Help my pp is very hard because this works! :))) XDD ; \nHello love! This should be in a new line! \nHippopotamus!12 Hippopotamus! Hippopotamus!";
    float scroll = 0.99f;
    float intensity = 10.0f;
    glm::vec3 color = glm::vec3(1.0f);
    float linear = 0.014;
    float quadratic = 0.0007;
    
    
    void OnUpdate() override
	{
		camera.ProcessKeyboard(Rosewood::Application::GetDeltaTime());
        {
            Rosewood::GraphicsCommand::SetClearColor(glm::vec4(0.1f, 0.12f, 0.1f, 1.0f));
            Rosewood::GraphicsCommand::Clear();
        }
        
        //Rosewood::BatchRenderer::ResetStats();
        Rosewood::DeferredRenderer::Begin(camera.GetCamera().GetViewProjectionMatrix());
        
        Rosewood::DeferredRenderer::Submit(mesh, {0.0f, 0.0f, 0.0f}, {128.0f, 128.0f, 1.0f});
        
        Rosewood::DeferredRenderer::Submit(mesh, {100.0f, 10.0f, 0.0f}, {128.0f, 128.0f, 1.0f});

        Rosewood::DeferredRenderer::Submit(mesh, {10.0f, 400.0f, 0.0f}, {128.0f, 128.0f, 1.0f});

        float mouseX = Rosewood::Input::GetMouseX() + camera.GetCamera().GetPosition().x;
        float mouseY = Rosewood::Input::GetMouseY() + camera.GetCamera().GetPosition().y;

        Rosewood::DeferredRenderer::DrawPointLight(glm::vec3(mouseX, mouseY, scroll), color, intensity, 1.0, linear, quadratic);
        //Rosewood::DeferredRenderer::AddPointLight(glm::vec3(mouseX, mouseY, scroll), color, intensity, 1.0, linear, quadratic);

        //Rosewood::BatchRenderer::DrawQuad(glm::vec3(pos.x-150.0f, pos.y-150.0f, 0.0f), glm::vec2(300.0f, 300.0f), texture, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), col);
                
        Rosewood::DeferredRenderer::End();
                
        
    
	}
    float col[3] {1.0f, 1.0f, 1.0f};

	void OnImGuiRender() override
	{
		auto stats = Rosewood::BatchRenderer::GetStats();
		ImGui::Begin("This is 2D Spritebatch System", &open, 0);
		ImGui::Text("Camera Pos: %f, %f, %f", camera.GetCamera().GetPosition().x, camera.GetCamera().GetPosition().y, camera.GetCamera().GetPosition().z);
        ImGui::Text("Batch stats: %i, %i", stats.DrawCount, stats.QuadCount);
        ImGui::Text("Scroll: %f", scroll);

		ImGui::Text("FPS:");
		float deltaTime = 1.0f / (float)(Rosewood::Application::GetDeltaTime());
		ImGui::InputFloat("hz", &deltaTime, 0.0f, 0.0f, 5, ImGuiInputTextFlags_None);
        ImGui::InputFloat("Linear", &linear, 0.1f, 0.0f, 16, ImGuiInputTextFlags_None);
        ImGui::InputFloat("Quadratic", &quadratic, 0.1f, 0.0f, 16, ImGuiInputTextFlags_None);
        ImGui::InputFloat("Intensity", &intensity, 1.0f, 0.0f, 3, ImGuiInputTextFlags_None);
        
        ImGui::ColorPicker3("Color Picker", col);
        color = {col[0], col[1], col [2]};


		int w = scrWidth;
		int h = scrHeight;
		ImGui::InputInt("px", &w);
        ImGui::InputInt("px", &h);
        //myTexture.Bind(0);
        ImGui::Image((void*)Rosewood::DeferredRenderer::GetAlbedoID(), {192, 108});
        ImGui::Image((void*)Rosewood::DeferredRenderer::GetPosID(), {192, 108});
        ImGui::Image((void*)Rosewood::DeferredRenderer::GetNormalID(), {192, 108});


		
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
        RW_TRACE(e.ToString());
        if(e.GetMouseButton() == MOUSE_BUTTON_LEFT)
        {
            float mouseX = Rosewood::Input::GetMouseX() + camera.GetCamera().GetPosition().x;
            float mouseY = Rosewood::Input::GetMouseY() + camera.GetCamera().GetPosition().y;
            //Rosewood::DeferredRenderer::AddPointLight(glm::vec3(mouseX, mouseY, scroll), color, intensity, 1.0, linear, quadratic);
        }
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
        scroll += e.GetYOffset();

		return false;
	}

	bool OnKeyPressedEvent(Rosewood::KeyPressedEvent& e)
	{
		int key = e.GetKeyCode();
		if (key == KEY_R)
			Rosewood::Application::Get().GetWindow().LockCursor();
		else if (key == KEY_T)
			Rosewood::Application::Get().GetWindow().UnlockCursor();
        else if (key == KEY_F)
            sound->Play();
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


