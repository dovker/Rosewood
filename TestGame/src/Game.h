#pragma once

#include "Rosewood.h"
#include "imgui.h"
#include "2DCameraController.h"
#include "Entity/Entity.h"
#include "Entity/Player.h"


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
        static void SetCamera(Camera* cam) { m_Camera = cam; }
        static Rosewood::AssetManager* GetAssetManager() {return m_AssetManager;}
        
    private:
        Game();
        static Game* s_Instance;
        static int m_ScreenWidth, m_ScreenHeight;
        static Rosewood::AssetManager* m_AssetManager;
        
    };
    
}

