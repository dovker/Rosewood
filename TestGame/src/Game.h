#include "Rosewood.h"
#include "imgui.h"
#include "2DCameraController.h"
#include "Entity/Entity.h"

#ifndef Game_h
#define Game_h

namespace TestGame {
    class Game
    {
    public:
        void OnLoad();
        void OnUpdate();
        void OnDraw();
        void OnUnload();
        void OnImGuiRender();
        void OnMouseButtonPressed(int button);
        void OnMouseButtonReleased(int button);
        void OnMouseMoved(float x, float y);
        void OnMouseScrolled(float xOffset, float yOffset);
        void OnKeyPressed(int button);
        void OnKeyReleased(int button);
        void OnWindowResize(int w, int h);
        
        static int GetWidth() { return m_ScreenWidth; }
        static int GetHeight() { return m_ScreenHeight; }
        
        static Game* Get();
        static Camera* GetCamera() { return m_Camera; }
        static void SetCamera(Camera* cam) { m_Camera = cam; }
        static Rosewood::AssetManager* GetAssetManager() {return m_AssetManager;}
        
    private:
        Game();
        static Game* s_Instance;
        static std::vector<Entity> m_Entities;
        static int m_ScreenWidth, m_ScreenHeight;
        static Camera* m_Camera;
        static Rosewood::AssetManager* m_AssetManager;
        
    };
    Game* Game::s_Instance = nullptr;
    std::vector<Entity> Game::m_Entities = std::vector<Entity>();
    int Game::m_ScreenWidth = 0;
    int Game::m_ScreenHeight = 0;
    Rosewood::AssetManager* Game::m_AssetManager = nullptr;
    Camera* Game::m_Camera = nullptr;
}

#endif /* Game_h */
