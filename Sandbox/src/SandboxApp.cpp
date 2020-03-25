#include <Rosewood.h>

class Sandbox : public Rosewood::Application
{
public:

	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Rosewood::Application* Rosewood::CreateApplication()
{

	return new Sandbox();
}