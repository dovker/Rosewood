#include "Rosewood.h"
#include "imgui.h"
#include "Scene/Scene.h"
#include "Game.h"

namespace TestGame {


    Game::Game()
        : Layer("Example") {}

    void Game::OnAttach()
    {

        Rosewood::Renderer2D::Init();

        m_Scene = new Scene();
        
        m_Scene->OnLoad();
    }

    void Game::OnUpdate(Rosewood::Timestep timestep)
    {
        m_Scene->OnUpdate(timestep);
                
        m_Scene->OnDraw();
    }
    
    void Game::OnDetach()
    {
        m_Scene->OnUnload();
        delete m_Scene;
    }
    
    
    bool open = true;
    void Game::OnImGuiRender()
    {
        auto stats = Rosewood::BatchRenderer::GetStats();
        ImGui::Begin("This is 2D Spritebatch System", &open, 0);
        ImGui::Text("Batch stats: %i, %i", stats.DrawCount, stats.QuadCount);

        ImGui::Text("FPS:");
        //float deltaTime = 1.0f / (float)(Rosewood::Application::GetDeltaTime());
        //ImGui::InputFloat("hz", &deltaTime, 0.0f, 0.0f, nullptr, ImGuiInputTextFlags_None);
        
        ImGui::Separator();
                    
        ImGui::End();
    }

    void Game::OnEvent(Rosewood::Event& e)
    {
        m_Scene->OnEvent(e);
    }
    

}


