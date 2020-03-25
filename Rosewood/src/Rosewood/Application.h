#pragma once

#include "Core.h"

namespace Rosewood
{
	class ROSEWOOD_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	};

	//Has to be defined in CLIENT
	Application* CreateApplication();
}
