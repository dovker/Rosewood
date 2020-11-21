#include "Rosewood.h"
#include "Rosewood/EntryPoint.h"

#include "Game.h"


class Sandbox : public Rosewood::Application
{
public:

    Sandbox()
    {
        PushLayer(new TestGame::Game());
    }

    ~Sandbox()
    {
        Rosewood::BatchRenderer::Shutdown();

    }
};

Rosewood::Application* Rosewood::CreateApplication()
{
    
    return new Sandbox();
}


