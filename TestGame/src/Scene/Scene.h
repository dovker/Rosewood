#pragma once
#include "Rosewood.h"
#include "../Entity/Entity.h"
#include "../Entity/Player.h"
#include "../Map/Map.h"
#include "../Map/Tile.h"


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

        Map* GetMap();
    private:
        std::vector<Entity*> m_Entities;
        Map* m_Map;
        Rosewood::Ref<Rosewood::Scene> m_Scene;
    };
    
}

