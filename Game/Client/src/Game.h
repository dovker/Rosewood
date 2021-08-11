#pragma once
#include "Rosewood.h"
#include "Scene/Scene.h"

namespace TestGame
{
    class Game : public Rosewood::Layer
    {
    public:
        Game();
        virtual ~Game() = default;

        virtual void OnAttach() override;
        virtual void OnDetach() override;

        void OnUpdate(Rosewood::Timestep timestep) override;
        virtual void OnImGuiRender() override;
        void OnEvent(Rosewood::Event& e) override;

        static Scene* GetScene();
    private:
        static Scene* s_Scene;
    };

}

