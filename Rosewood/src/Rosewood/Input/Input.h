#pragma once
#include "Rosewood/Core/Core.h"
#include <rwpch.h>

namespace Rosewood
{
	class  Input
	{
	public:

		static bool IsKeyPressed(int keycode)	;
		static bool IsMouseButtonPressed(int button);
		static std::pair<float, float> GetMousePos(); 
		static float GetMouseX()					;
		static float GetMouseY()					;
	};
}