#pragma once
#include "Rosewood/Core.h"
#include <rwpch.h>
#include "Rosewood/Input/Input.h"

namespace Rosewood
{
	class  WindowsInput : public Input
	{
	protected:

		virtual bool IsKeyPressedPlatform(int keycode);
		virtual bool IsMouseButtonPressedPlatform(int button);
		virtual std::pair<float, float> GetMousePosPlatform();
		virtual float GetMouseXPlatform();
		virtual float GetMouseYPlatform();

	};
}
