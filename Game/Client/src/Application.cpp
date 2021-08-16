#include "Rosewood.h"
#include "Rosewood/Core/EntryPoint.h"

#include "Game.h"

class GameApplication : public Rosewood::Application
{
public:

    GameApplication()
    {
        PushLayer(new Game::Game());
    }

    ~GameApplication()
    {
        Rosewood::Renderer2D::Shutdown();
    }
};

Rosewood::Application* Rosewood::CreateApplication()
{
    return new GameApplication();
}


