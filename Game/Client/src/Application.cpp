#include "Rosewood.h"
#include "Rosewood/Core/EntryPoint.h"

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
        Rosewood::Renderer2D::Shutdown();

    }
};

Rosewood::Application* Rosewood::CreateApplication()
{
    
    return new Sandbox();
}


