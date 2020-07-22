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
    //Rosewood::Ref<Rosewood::RenderMesh> mesh;

    Camera camera = Camera(glm::vec2( (float)scrWidth, (float)scrHeight));
    
    glm::vec2 pos, vel;
	
	ExampleLayer()
		: Layer("Example")
	{
        assetManager.Load<Rosewood::Texture>("Content/dvd_logo.png", "Deferred_Albedo");
        assetManager.Load<Rosewood::Sound>("Content/sound.mp3", "Sound");
        assetManager.Load<Rosewood::Texture>("Content/SpriteFont.png", "Sprite_Font");


        texture = assetManager.Get<Rosewood::Texture>("Deferred_Albedo");
        sound = assetManager.Get<Rosewood::Sound>("Sound");
        fontTexture = assetManager.Get<Rosewood::Texture>("Sprite_Font");
                
        font = Rosewood::SpriteFont::Create(fontTexture, ";ABC", 16, 16);

        Rosewood::BatchRenderer::Init();
        pos = {0.0f, 0.0f};
        vel = {120.0f, 120.0f};

	}

	bool open = true;
    glm::vec4 col = glm::vec4(1.0f);
    std::string text = "ABC; ABA; BABABA    B";
    
    void OnUpdate() override
	{
		camera.ProcessKeyboard(Rosewood::Application::GetDeltaTime());
        {
            Rosewood::GraphicsCommand::SetClearColor(glm::vec4(0.1f, 0.12f, 0.1f, 1.0f));
            Rosewood::GraphicsCommand::Clear();
        }
        if (pos.x + (vel.x * Rosewood::Application::GetDeltaTime()) >= scrWidth || pos.x + (vel.x * Rosewood::Application::GetDeltaTime()) <=0)
        {
            vel.x *= -1;
            col.r = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
            col.g = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
            col.b = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
            
            float pan = ( pos.x / scrWidth ) - 0.5;
            sound->SetPan(pan);
            sound->Play();

        }
        if (pos.y + (vel.y * Rosewood::Application::GetDeltaTime())>= scrHeight || pos.y + (vel.y * Rosewood::Application::GetDeltaTime()) <=0)
        {
            vel.y *= -1;
            col.r = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
            col.g = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
            col.b = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
            
            float pan = ( pos.x / scrWidth ) - 0.5;
            sound->SetPan(pan);
            sound->Play();
            sound->SetSpeed(1.0-static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX)/3);
        }
        pos += vel * Rosewood::Application::GetDeltaTime();
        
        Rosewood::BatchRenderer::ResetStats();
        Rosewood::BatchRenderer::Begin(camera.GetCamera());
        
        Rosewood::BatchRenderer::DrawQuad(glm::vec3(pos.x-150.0f, pos.y-150.0f, 0.0f), glm::vec2(300.0f, 300.0f), texture, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f), col);
        
        font->DrawString({100, 100}, text, {1.0f, 1.0f, 1.0f, 1.0f});
        
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
        //myTexture.Bind(0);
        //ImGui::Image((void*)m_Framebuffer->GetColorAttachmentRendererID(), {192, 108});
		
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


