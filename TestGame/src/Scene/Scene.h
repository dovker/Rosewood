#pragma once
#include "Rosewood.h"
#include "CameraController.h"
#include "../Entity/Entity.h"
#include "../Entity/Player.h"
#include "../Map/Map.h"




namespace TestGame {
    class Scene
    {
    public:
        Scene();
        void OnLoad(Rosewood::AssetManager &assetManager);
        void OnUpdate();
        void OnDraw();
        void OnUnload(Rosewood::AssetManager &assetManager);
        void OnEvent(Rosewood::Event &e);
        void OnWindowResize(int w, int h);
        
        Camera* GetCamera() { return m_Camera; }
        void SetCamera(Camera* cam) { m_Camera = cam; }
        
    private:
        std::vector<Entity*> m_Entities;
        Camera* m_Camera;
        Map* m_Map;
    };
    
}

