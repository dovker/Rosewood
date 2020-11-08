#include "Rosewood.h"
#include "imgui.h"
#include "Game.h"
#include "Entity/Entity.h"
#include "Entity/Player.h"

namespace TestGame {


    Game::Game()
    {
        Rosewood::Application::Get().GetWindow().SetTitle("TestGame");
        
        m_AssetManager = new Rosewood::AssetManager();
        m_ScreenWidth = Rosewood::Application::Get().GetWindow().GetWidth();
        m_ScreenHeight = Rosewood::Application::Get().GetWindow().GetHeight();
        m_Camera = new Camera(glm::vec2(m_ScreenWidth, m_ScreenHeight));
        
        
        Rosewood::BatchRenderer::Init();
    }
    Game* Game::Get()
    {
        if (s_Instance == nullptr)
        {
            s_Instance = new Game();
        }
        return s_Instance;
    }
    void Game::OnLoad()
    {
        
    }
    void Game::OnUpdate()
    {
        
    }
    void Game::OnDraw()
    {
        {
            Rosewood::GraphicsCommand::SetClearColor(glm::vec4(0.1f, 0.12f, 0.1f, 1.0f));
            Rosewood::GraphicsCommand::Clear();
        }
        
        Rosewood::BatchRenderer::Begin(m_Camera->GetCamera());
        
        
        
        Rosewood::BatchRenderer::End();
    }
    void Game::OnUnload()
    {
        
    }

    
    void Game::OnWindowResize(int w, int h)
    {
        m_Camera->ProcessScreenResize(glm::vec2(w, h));
        Rosewood::GraphicsCommand::SetViewport(0, 0, w, h);
    }

    void Game::OnImGuiRender(){}
    void Game::OnMouseButtonPressed(int button){}
    void Game::OnMouseButtonReleased(int button){}
    void Game::OnMouseMoved(float x, float y){}
    void Game::OnMouseScrolled(float xOffset, float yOffset){}
    void Game::OnKeyPressed(int button){}
    void Game::OnKeyReleased(int button){}
}
