#include "Rosewood.h"
#include "Rosewood/EntryPoint.h"
#include "imgui.h"
#include "Sofa.h"
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
    
    Sofa sofa;
    
    Rosewood::Ref<Rosewood::SpriteFont> font;
    
    Rosewood::AssetManager assetManager;
    Rosewood::Ref<Rosewood::VertexArray> m_VertexArray;
    Rosewood::Ref<Rosewood::Framebuffer> m_Framebuffer;
    Rosewood::Ref<Rosewood::Sound> sound;
    
    //Rosewood::Sound sound = Rosewood::Audio::LoadAudioSource("/Users/dovydas/Documents/GitHub/Rosewood/assets/sound.mp3");
    Rosewood::Ref<Rosewood::RenderMesh> mesh;
    Rosewood::Ref<Rosewood::RenderMesh> flatMesh;
    Rosewood::Ref<Rosewood::RenderMesh> planeMesh;
    
    Rosewood::Ref<Rosewood::DecalLight> decal;


    CameraControl camera = CameraControl(glm::vec2( (float)scrWidth, (float)scrHeight));
    
    bool open = true;
    std::string text = "Help my pp is very hard because this works! :))) XDD ; \nHello love! This should be in a new line! \nHippopotamus!12 Hippopotamus! Hippopotamus!";
    float scroll = 0.0f;
    float intensity = 1.0f;
    float intensityDecal = 1.0f;

    float gamma = 2.2f;
    float exposure = 1.0f;
    glm::vec3 color = glm::vec3(1.0f);
    glm::vec3 colorDecal = glm::vec3(1.0f);

    glm::vec3 bcs = glm::vec3(0.0f, 1.0f, 1.0f);
    glm::vec2 bwpoint = glm::vec2(0.0f, 1.0f);
    float linear = 0.014;
    float quadratic = 0.0007;
    
    glm::vec3 direction = {0.0f, 0.0f, -1.0f};
    
    glm::vec3 ambient = glm::vec3(0.1f);
    float mouseX = 0.0f;
    float mouseY = 0.0f;
	
	ExampleLayer()
		: Layer("Example")
	{
        Rosewood::Ref<Rosewood::Texture> albedo = assetManager.Load<Rosewood::Texture>("Content/TestBox.png", "Deferred_Albedo");
        Rosewood::Ref<Rosewood::Texture> normal = assetManager.Load<Rosewood::Texture>("Content/Deferred_Normal.png", "Deferred_Normal");
        Rosewood::Ref<Rosewood::Texture> spec = assetManager.Load<Rosewood::Texture>("Content/Deferred_Specular.png", "Deferred_Specular");
        Rosewood::Ref<Rosewood::Texture> lightTex = assetManager.Load<Rosewood::Texture>("Content/awesomeface.png", "DecalLight");
        
        sofa.Load(assetManager);

        texture = lightTex;

        
        assetManager.Load<Rosewood::Sound>("Content/sound.mp3", "Sound");
        assetManager.Load<Rosewood::Texture>("Content/Chroma.png", "Sprite_Font");
        
//        mesh = Rosewood::RenderMesh::Create(
//        std::vector<float>{-1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
//                           -1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
//                            1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f,
//                            1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f},
//        std::vector<uint32_t>{ 0, 1, 2, 2, 3, 0 },
//        std::vector<Rosewood::Ref<Rosewood::Texture>>{albedo, normal, spec});
        mesh = Rosewood::RenderMesh::CreateFoldedQuad(std::vector<Rosewood::Ref<Rosewood::Texture>>{albedo, normal, spec}, 0.5f);
        flatMesh = Rosewood::RenderMesh::CreateFlatQuad(std::vector<Rosewood::Ref<Rosewood::Texture>>{albedo, normal, spec});
        planeMesh= Rosewood::RenderMesh::CreatePerpendicularQuad(std::vector<Rosewood::Ref<Rosewood::Texture>>{albedo, normal, spec});

        sound = assetManager.Get<Rosewood::Sound>("Sound");
        fontTexture = assetManager.Get<Rosewood::Texture>("Sprite_Font");
        
        decal = Rosewood::DecalLight::Create(texture, {mouseX, mouseY, 0.0f}, direction, color * intensityDecal, {texture->GetWidth(), texture->GetHeight()});
        
        font = Rosewood::SpriteFont::Create(fontTexture, "!\"#$%&\'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ ", 9, 9);

        Rosewood::DeferredRenderer::Init();

	}

	
    void OnUpdate(Rosewood::Timestep timestep) override
	{
		camera.ProcessKeyboard(timestep.GetSeconds());
        {
            Rosewood::GraphicsCommand::SetClearColor(glm::vec4(0.1f, 0.12f, 0.1f, 1.0f));
            Rosewood::GraphicsCommand::Clear();
        }
        
        //POST PROCESSING
        Rosewood::DeferredRenderer::SetAmbient(ambient);
        
        Rosewood::DeferredRenderer::SetGamma(gamma);

        Rosewood::DeferredRenderer::SetExposure(exposure);
        
        Rosewood::DeferredRenderer::SetBCS(bcs);
        
        Rosewood::DeferredRenderer::SetBWPoint(bwpoint);
        
        
        
        Rosewood::DeferredRenderer::Begin(camera.GetCamera());

        //Rosewood::DeferredRenderer::Submit(planeMesh, {200.0f, -200.0f, -200.0f}, {200, 200, 200});
//
        //
        //Rosewood::DeferredRenderer::Submit(flatMesh, {200.0f, 0.0f, 0.0f}, {200, 200, 200});
        //
        //Rosewood::DeferredRenderer::Submit(planeMesh, {200.0f, 200.0f, 0.0f}, {200, 200, 200});
        
        sofa.Draw(glm::vec3(0.0f, 0.0f, 0.0f));
        
        mouseX = Rosewood::Input::GetMouseX() + camera.GetCamera().GetPosition().x;
        mouseY = Rosewood::Input::GetMouseY() + camera.GetCamera().GetPosition().y;
        
        decal->SetPosRot(glm::vec3(mouseX, mouseY, scroll), direction);
        decal->color = colorDecal * intensityDecal;
        
        Rosewood::DeferredRenderer::SubmitDecalLight(decal);

        
        Rosewood::DeferredRenderer::BeginLights();

        

        
        Rosewood::DeferredRenderer::DrawPointLight(glm::vec3(mouseX, mouseY, scroll), color, intensity, 1.0, linear, quadratic);
        
        Rosewood::DeferredRenderer::DrawDecals();


        Rosewood::DeferredRenderer::End();
                
        
    
	}
    float col[3] {1.0f, 1.0f, 1.0f};
    float colDec[3] {1.0f, 1.0f, 1.0f};

    float ambCol[3] {0.1f, 0.1f, 0.1f};
    float dir[3] {0.0f, 0.0f, -1.0f};



	void OnImGuiRender() override
	{
		auto stats = Rosewood::BatchRenderer::GetStats();
		ImGui::Begin("This is 2D Spritebatch System", &open, 0);
		ImGui::Text("Camera Pos: %f, %f, %f", camera.GetCamera().GetPosition().x, camera.GetCamera().GetPosition().y, camera.GetCamera().GetPosition().z);
        ImGui::Text("Batch stats: %i, %i", stats.DrawCount, stats.QuadCount);
        ImGui::Text("Scroll: %f", scroll);

        
        ImGui::Separator();

        ImGui::SliderFloat3("Direction", dir, -1.0f, 1.0f);
        direction = glm::normalize(glm::vec3(dir[0], dir[1], dir[2]));
        
        ImGui::SliderFloat("Exposure", &exposure, 0.0f, 10.0f);
        ImGui::SliderFloat("Gamma", &gamma, 0.0f, 10.0f);


        
        ImGui::SliderFloat("Brightness", &bcs.x, -1.0f, 1.0f);
        ImGui::SliderFloat("Contrast", &bcs.y, 0.0f, 10.0f);
        ImGui::SliderFloat("Saturation", &bcs.z, 0.0f, 10.0f);
        
        ImGui::SliderFloat("Black Point", &bwpoint.x, 0.0f, 1.0f);
        ImGui::SliderFloat("White Point", &bwpoint.y, -1.0f, 1.0f);

        
        if(ImGui::Button("RECOMPILE RENDERER SHADERS")) Rosewood::DeferredRenderer::ReloadShaders();
        
        ImGui::Separator();
        
        
        ImGui::ColorPicker3("Decal Color", colDec);
        colorDecal = {colDec[0], colDec[1], colDec [2]};
        ImGui::InputFloat("Decal Intensity", &intensityDecal);

        
        ImGui::ColorPicker3("Light Color", col);
        color = {col[0], col[1], col [2]};
        
        ImGui::ColorPicker3("Ambient Color", ambCol);
        ambient = {ambCol[0], ambCol[1], ambCol[2]};
        
        ImGui::InputFloat("Linear", &linear, 0.1f, 0.0f, "%.19f");
        ImGui::InputFloat("Quadratic", &quadratic, 0.1f, 0.0f, "%.19f");
        ImGui::InputFloat("Intensity", &intensity);
        ImGui::Separator();

		int w = scrWidth;
		int h = scrHeight;
		ImGui::InputInt("px", &w);
        ImGui::InputInt("px", &h);
        //myTexture.Bind(0);
        ImGui::Image((void*)Rosewood::DeferredRenderer::GetAlbedoID(), {576, 324});
        ImGui::Image((void*)Rosewood::DeferredRenderer::GetPosID(), {576, 324});
        ImGui::Image((void*)Rosewood::DeferredRenderer::GetNormalID(), {576, 324});
        ImGui::Image((void*)Rosewood::DeferredRenderer::GetLightID(), {576, 324});
        ImGui::Image((void*)Rosewood::DeferredRenderer::GetDepthID(), {576, 324});
        ImGui::Image((void*)decal->depth->GetDepthAttachmentRendererID(), {576, 324});

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


