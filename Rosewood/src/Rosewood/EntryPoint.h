#pragma once

extern Rosewood::Application* Rosewood::CreateApplication();

int main(int argc, char** argv)
{
	Rosewood::Log::Init();
	auto app = Rosewood::CreateApplication();
	app->Run();
	delete app;
}
