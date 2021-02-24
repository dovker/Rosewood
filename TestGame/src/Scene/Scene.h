#pragma once
#include "Rosewood.h"
#include "../Camera/CameraController.h"
#include "../Entity/Entity.h"
#include "../Entity/Player.h"
#include "../Map/Map.h"

namespace TestGame {

    class Scene
    {
    public:
        Scene();
        void OnLoad();
        void OnUpdate(Rosewood::Timestep timestep);
        void OnDraw();
        void OnUnload();
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

