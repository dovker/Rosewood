#include <Rosewood.h>

class ExampleLayer : public Rosewood::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		RW_INFO(" Ha Ha Pee Pee Updated LOLOLOLOL");
		
	}

	void OnEvent(Rosewood::Event& event) override
	{
		RW_TRACE("{0}", event);
	}
};

class Sandbox : public Rosewood::Application
{
public:

	Sandbox()
	{
		PushLayer(new ExampleLayer());  
	}

	~Sandbox()
	{

	}
};

Rosewood::Application* Rosewood::CreateApplication()
{

	return new Sandbox();
}