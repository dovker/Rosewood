#pragma once
#include "Rosewood.h"
#include "Scene.h"

namespace TestGame
{
    class Game : public Rosewood::Layer
    {
    public:
        Game();
        virtual ~Game() = default;

        virtual void OnAttach() override;
        virtual void OnDetach() override;

        void OnUpdate() override;
        virtual void OnImGuiRender() override;
        void OnEvent(Rosewood::Event& e) override;
    private:
        Rosewood::Ref<Scene> m_Scene;
        Rosewood::AssetManager m_AssetManager;

    };

}
