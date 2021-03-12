#pragma once
#include "Rosewood.h"
#include "../Camera/CameraController.h"
#include "../Entity/Entity.h"
#include "../Map/Map.h"
#include "../Map/Tile.h"


namespace TestGame {

    class TileEditor
    {
    public:
        TileEditor();
        void OnLoad();
        void OnUpdate(Rosewood::Timestep timestep);
        void OnDraw();
        void OnImGuiDraw();
        void OnUnload();
        void OnEvent(Rosewood::Event &e);
        void OnWindowResize(int w, int h);
        
        GameCamera* GetCamera() { return m_Camera; }
        void SetCamera(GameCamera* cam) { m_Camera = cam; }
        
        Map* GetMap();
    private:
        GameCamera* m_Camera;
        Map* m_Map;
    };
    
}

