#include "Rosewood.h"
#include "imgui.h"
#include "Scene.h"
#include "Game.h"

namespace TestGame {


    Game::Game()
        : Layer("Example") {}

    void Game::OnAttach()
    {
        m_AssetManager = Rosewood::AssetManager();
        Rosewood::GraphicsCommand::ToggleBlending(true);
        Rosewood::GraphicsCommand::ToggleDepthTest(true);

        Rosewood::BatchRenderer::Init();

        m_Scene = Rosewood::CreateRef<Scene>();
        
        m_Scene->OnLoad(m_AssetManager);
    }

    void Game::OnUpdate(Rosewood::Timestep timestep)
    {
        m_Scene->OnUpdate(timestep);
        
        //std::cout<<1.0/timestep.GetSeconds()<<std::endl;
        
        m_Scene->OnDraw();
    }
    
    void Game::OnDetach()
    {
        m_Scene->OnUnload(m_AssetManager);
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


