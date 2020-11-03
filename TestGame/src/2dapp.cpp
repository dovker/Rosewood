#include "Rosewood.h"
#include "imgui.h"
#include "2DCameraController.h"


class ExampleLayer : public Rosewood::Layer
{
public:
	unsigned int scrWidth = Rosewood::Application::Get().GetWindow().GetWidth();
	unsigned int scrHeight = Rosewood::Application::Get().GetWindow().GetHeight();
	
    Rosewood::Ref<Rosewood::Texture> texture;
    Rosewood::Ref<Rosewood::Texture> fontTexture;

    
    Rosewood::Ref<Rosewood::SpriteFont> font;
    
    Rosewood::AssetManager assetManager;
    Rosewood::Ref<Rosewood::Sound> sound;
    
    //Rosewood::Sound sound = Rosewood::Audio::LoadAudioSource("/Users/dovydas/Documents/GitHub/Rosewood/assets/sound.mp3");
    Camera camera = Camera(glm::vec2( (float)scrWidth, (float)scrHeight));
    
	
	ExampleLayer()
		: Layer("Example")
	{
        Rosewood::Ref<Rosewood::Texture> albedo = assetManager.Load<Rosewood::Texture>("Content/TestBox.png", "Deferred_Albedo");
        
        assetManager.Load<Rosewood::Sound>("Content/sound.mp3", "Sound");
        assetManager.Load<Rosewood::Texture>("Content/Chroma.png", "Sprite_Font");

        sound = assetManager.Get<Rosewood::Sound>("Sound");
        fontTexture = assetManager.Get<Rosewood::Texture>("Sprite_Font");
        
        font = Rosewood::SpriteFont::Create(fontTexture, "!\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ ", 9, 9);

        Rosewood::BatchRenderer::Init();
        
	}

    void OnUpdate() override
	{
		camera.ProcessKeyboard(Rosewood::Application::GetDeltaTime());
        {
            Rosewood::GraphicsCommand::SetClearColor(glm::vec4(0.1f, 0.12f, 0.1f, 1.0f));
            Rosewood::GraphicsCommand::Clear();
        }
        
        
        
        Rosewood::BatchRenderer::Begin(camera.GetCamera());

        
                
        Rosewood::DeferredRenderer::End();
                
        
    
	}
    float col[3] {1.0f, 1.0f, 1.0f};
    float ambCol[3] {0.1f, 0.1f, 0.1f};



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
	}

	bool OnMouseButtonPressedEvent(Rosewood::MouseButtonPressedEvent& e)
	{
        //RW_TRACE(e.ToString());
        if(e.GetMouseButton() == MOUSE_BUTTON_LEFT)
        {
            float mouseX = Rosewood::Input::GetMouseX() + camera.GetCamera().GetPosition().x;
            float mouseY = Rosewood::Input::GetMouseY() + camera.GetCamera().GetPosition().y;
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


