#include "Rosewood.h"
#include "imgui.h"
#include "Game.h"
#include "Shared/Common.h"

const std::string Rosewood::FileSystem::ProjectRoot = "../../../Game/Client/";

namespace Game {
    class Client : public Rosewood::ClientInterface<GameMessages>
    {
    public:
        Client()
            : Rosewood::ClientInterface<GameMessages>()
        {}
    };

    Client client;
    
    Game::Game()
        : Layer("Example") {}
    void Game::OnAttach()
    {
        Rosewood::Renderer2D::Init();
        Rosewood::Benchmark::Init();

        Rosewood::AssetLoader::LoadAssets(Rosewood::FileSystem::GetPath("Index.json"));

        Rosewood::SceneManager::SetScene(Rosewood::Scene::Create());
        client.Connect("127.0.0.1", 25567, true, Rosewood::FileSystem::GetPath("certificate.crt"));
    }

    void Game::OnUpdate(Rosewood::Timestep timestep)
    {
        if(client.IsConnected())
        {
            Rosewood::SceneManager::OnUpdateRuntime(timestep);

            {
                Rosewood::GraphicsCommand::SetClearColor(glm::vec4(0.1f, 0.12f, 0.1f, 1.0f));
                Rosewood::GraphicsCommand::Clear();
            }

            Rosewood::BatchRenderer::ResetStats();

            Rosewood::SceneManager::OnRenderRuntime();
        }    
    }
    
    void Game::OnDetach()
    {
        
    }
    
    bool open = true;
    char txt[32] = "Scene.yaml";
    void Game::OnImGuiRender()
    {
        auto stats = Rosewood::BatchRenderer::GetStats();
        ImGui::Begin("This is 2D Spritebatch System", &open, 0);
        ImGui::Text("Batch stats: %i, %i", stats.DrawCount, stats.QuadCount);

        ImGui::Text("Frame Time: %.3fms | %iFPS", Rosewood::Application::GetDeltaTime() * 1000.0f, (int)(1.0f/Rosewood::Application::GetDeltaTime()));

        if(ImGui::Button("Export Assets"))
        {
            Rosewood::AssetLoader::ExportAssetIndex(Rosewood::FileSystem::GetPath("Index.json"), Rosewood::FilePathType::PROJECT);
        }
        ImGui::InputText("Scene FileName", txt, 32, ImGuiInputTextFlags_None);
        if(ImGui::Button("Export Scene")) 
        {
            Rosewood::SceneManager::SaveScene(Rosewood::FileSystem::GetPath(txt));
        }
        if(ImGui::Button("Load Scene")) 
        {
            Rosewood::SceneManager::LoadScenByPath(Rosewood::FileSystem::GetPath(txt));
        }

        ImGui::Separator();
        ImGui::Text("PROFILER");
        ImGui::Separator();

        for(auto i : Rosewood::Benchmark::GetData())
        {
            ImGui::TextColored({0.2f, 1.0f, 0.2f, 1.0f}, "%s: %.3fms", i.first.c_str(), i.second);
            ImGui::Separator();
        }
        Rosewood::Benchmark::Reset();
        
        ImGui::Separator();
                    
        ImGui::End();
    }

    void Game::OnEvent(Rosewood::Event& e)
    {
        Rosewood::SceneManager::OnEvent(e);
    }

}


