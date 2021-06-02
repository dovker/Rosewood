#include "Rosewood.h"
#include "imgui.h"
#include "Scene/Scene.h"
#include "Game.h"


const std::string Rosewood::FileSystem::ProjectRoot = "../../../TestGame/";

namespace TestGame {

    Scene* Game::s_Scene = nullptr;

    
    Game::Game()
        : Layer("Example") {}

    Rosewood::LuaState* state;
    void Game::OnAttach()
    {
        Rosewood::Renderer2D::Init();
        Rosewood::Benchmark::Init();

        state = new Rosewood::LuaState();

        state->ExecuteScript(Rosewood::FileSystem::GetPath("Scripts/Script.lua"));
        state->InsistGlobal("SampleScript");
        state->CallVoidFunction("OnCreate");
        //Do on seperate threads
        //state.CloseGlobal();
        state->ClearStack();

        s_Scene = new Scene();
        
        s_Scene->OnLoad();
    }

    void Game::OnUpdate(Rosewood::Timestep timestep)
    {
        s_Scene->OnUpdate(timestep);
        
        {
            Rosewood::BenchmarkTimer timer = Rosewood::BenchmarkTimer("Lua OnUpdate");
            
            state->InsistGlobal("SampleScript");
            state->CallVoidFunction("OnUpdate");
            state->ClearStack();
            
        }
        s_Scene->OnDraw();
        
    }
    
    void Game::OnDetach()
    {
        s_Scene->OnUnload();
        delete s_Scene;
        delete state;
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


