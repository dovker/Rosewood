#include "Rosewood.h"
#include "imgui.h"
#include "Game.h"


class GameLayer : public Rosewood::Layer
{
public:
    TestGame::Game* game = TestGame::Game::Get();

    GameLayer()
        : Layer("Example")
    {
        game->OnLoad();
    }

    void OnUpdate() override
    {
        game->OnUpdate();
    }
    
    bool open = true;
    void OnImGuiRender() override
    {
        auto stats = Rosewood::BatchRenderer::GetStats();
        ImGui::Begin("This is 2D Spritebatch System", &open, 0);
        ImGui::Text("Batch stats: %i, %i", stats.DrawCount, stats.QuadCount);

        ImGui::Text("FPS:");
        float deltaTime = 1.0f / (float)(Rosewood::Application::GetDeltaTime());
        ImGui::InputFloat("hz", &deltaTime, 0.0f, 0.0f, 5, ImGuiInputTextFlags_None);
        
        ImGui::Separator();
        
        game->OnImGuiRender();
        
        ImGui::End();
    }
    void OnEvent(Rosewood::Event& event) override
    {
        Rosewood::EventDispatcher dispatcher(event);
        dispatcher.Dispatch<Rosewood::MouseButtonPressedEvent>(RW_BIND_EVENT_FN(GameLayer::OnMouseButtonPressedEvent));
        dispatcher.Dispatch<Rosewood::MouseButtonReleasedEvent>(RW_BIND_EVENT_FN(GameLayer::OnMouseButtonReleasedEvent));
        dispatcher.Dispatch<Rosewood::MouseMovedEvent>(RW_BIND_EVENT_FN(GameLayer::OnMouseMovedEvent));
        dispatcher.Dispatch<Rosewood::MouseScrolledEvent>(RW_BIND_EVENT_FN(GameLayer::OnMouseScrolledEvent));
        dispatcher.Dispatch<Rosewood::KeyPressedEvent>(RW_BIND_EVENT_FN(GameLayer::OnKeyPressedEvent));
        dispatcher.Dispatch<Rosewood::KeyReleasedEvent>(RW_BIND_EVENT_FN(GameLayer::OnKeyReleasedEvent));
        dispatcher.Dispatch<Rosewood::WindowResizeEvent>(RW_BIND_EVENT_FN(GameLayer::OnWindowResizeEvent));
    }

    bool OnMouseButtonPressedEvent(Rosewood::MouseButtonPressedEvent& e)
    {
        game->OnMouseButtonPressed(e.GetMouseButton());
        return false;
    }

    bool OnMouseButtonReleasedEvent(Rosewood::MouseButtonReleasedEvent& e)
    {
        game->OnMouseButtonReleased(e.GetMouseButton());

        return false;
    }

    bool firstMouse = true;

    bool OnMouseMovedEvent(Rosewood::MouseMovedEvent& e)
    {
        game->OnMouseMoved(e.GetX(), e.GetY());

        return false;
    }

    bool OnMouseScrolledEvent(Rosewood::MouseScrolledEvent& e)
    {
        game->OnMouseScrolled(e.GetXOffset(), e.GetYOffset());
        return false;
    }

    bool OnKeyPressedEvent(Rosewood::KeyPressedEvent& e)
    {
        game->OnKeyPressed(e.GetKeyCode());
        return false;
    }

    bool OnKeyReleasedEvent(Rosewood::KeyReleasedEvent& e)
    {
        game->OnKeyReleased(e.GetKeyCode());
        return false;
    }
    bool OnWindowResizeEvent(Rosewood::WindowResizeEvent& e)
    {
        game->OnWindowResize(e.GetWidth(), e.GetHeight());
        
        return false;
    }
};

class Sandbox : public Rosewood::Application
{
public:

    Sandbox()
    {
        PushLayer(new GameLayer());
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


