#pragma once

#include "Rosewood.h"
#include "imgui.h"
#include "2DCameraController.h"
#include "Entity/Entity.h"
#include "Entity/Player.h"
#include "../2DCameraController.h"


namespace TestGame {
    class Game
    {
    public:
        void OnLoad(Rosewood::AssetManager &assetManager);
        void OnUpdate();
        void OnDraw();
        void OnUnload();
        void OnWindowResize(int w, int h);
        
        Camera* GetCamera() { return m_Camera; }
         void SetCamera(Camera* cam) { m_Camera = cam; }
        
    private:
        static std::vector<Entity> m_Entities;
        Camera* m_Camera;
        
    };
    
}

