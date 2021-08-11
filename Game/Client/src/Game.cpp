#include "Rosewood.h"
#include "imgui.h"
#include "Scene/Scene.h"
#include "Game.h"


const std::string Rosewood::FileSystem::ProjectRoot = "../../../TestGame/";

namespace TestGame {

    Scene* Game::s_Scene = nullptr;

    
    Game::Game()
        : Layer("Example") {}

    Rosewood::Ref<Rosewood::Texture> GRASS;
    void Game::OnAttach()
    {
        Rosewood::Renderer2D::Init();
        Rosewood::Benchmark::Init();
        

        Rosewood::BinaryFile file(Rosewood::FileSystem::GetPath("grass.png"));

        {
            file.Write(Rosewood::FileSystem::GetPath("grass1.png"));
            Rosewood::Pack pack(Rosewood::FileSystem::GetRootPath() + Rosewood::FileSystem::GetFolderName() + ".zip");
            pack.AddFile("grass.png", file.GetData());
        }
        {
            Rosewood::Pack pack(Rosewood::FileSystem::GetRootPath() + Rosewood::FileSystem::GetFolderName() + ".zip");
            file.SetData(pack.ReadFile("grass.png"));
            file.Write(Rosewood::FileSystem::GetPath("grass123.png"));
        }

        Rosewood::AssetLoader::LoadAssets(Rosewood::FileSystem::GetPath("Index.json"));
        s_Scene = new Scene();
        
        s_Scene->OnLoad();
    }

    void Game::OnUpdate(Rosewood::Timestep timestep)
    {
        s_Scene->OnUpdate(timestep);
        
        s_Scene->OnDraw();
    }
    
    void Game::OnDetach()
    {
        s_Scene->OnUnload();
        delete s_Scene;
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


