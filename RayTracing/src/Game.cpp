#include "Rosewood.h"
#include "imgui.h"
#include "Game.h"

namespace TestGame {
    
    Game::Game()
        : Layer("Example") {}

    void Game::OnAttach()
    {
        Rosewood::Renderer2D::Init();
        Rosewood::Benchmark::Init();

    }

    void Game::OnUpdate(Rosewood::Timestep timestep)
    {
        
    }
    
    void Game::OnDetach()
    {
        
    }
    
    bool open = true;
    void Game::OnImGuiRender()
    {
        auto stats = Rosewood::BatchRenderer::GetStats();
        ImGui::Begin("This is 2D Spritebatch System", &open, 0);
        ImGui::Text("Batch stats: %i, %i", stats.DrawCount, stats.QuadCount);

        ImGui::Text("Frame Time: %.3fms | %iFPS", Rosewood::Application::GetDeltaTime() * 1000.0f, (int)(1.0f/Rosewood::Application::GetDeltaTime()));


        ImGui::Separator();
        ImGui::Text("PROFILER");
        ImGui::Separator();

        for(auto i : Rosewood::Benchmark::GetData())
        {
            ImGui::TextColored({0.2f, 1.0f, 0.2f, 1.0f}, "%s: %.3fms", i.first.c_str(), i.second);
            ImGui::Separator();
        }
        Rosewood::Benchmark::Reset();
        //float deltaTime = 1.0f / (float)(Rosewood::Application::GetDeltaTime());
        //ImGui::InputFloat("hz", &deltaTime, 0.0f, 0.0f, nullptr, ImGuiInputTextFlags_None);
        
        ImGui::Separator();
                    
        ImGui::End();
    }

    void Game::OnEvent(Rosewood::Event& e)
    {
        s_Scene->OnEvent(e);
    }
    
    Scene* Game::GetScene()
    {
        return s_Scene;
    }
}


