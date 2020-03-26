#pragma once

#ifdef RW_PLATFORM_WINDOWS

extern Rosewood::Application* Rosewood::CreateApplication();

int main(int argc, char** argv)
{
	Rosewood::Log::Init();
	RW_CORE_CRITICAL("My pp is very hard right now");
	RW_TRACE("Ok it's not as hard as it was just before lmao fucking boomer");

	auto app = Rosewood::CreateApplication();
	app->Run();
	delete app;
}
#endif