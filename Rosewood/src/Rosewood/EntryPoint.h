#pragma once

#ifdef RW_PLATFORM_WINDOWS

extern Rosewood::Application* Rosewood::CreateApplication();

int main(int argc, char** argv)
{
	Rosewood::Log::Init();
	auto app = Rosewood::CreateApplication();
	app->Run();
	delete app;
}
#endif