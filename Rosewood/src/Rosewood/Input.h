#pragma once
#include "Rosewood/Core.h"
#include <rwpch.h>

namespace Rosewood
{
	class ROSEWOOD_API Input
	{
	public:

		inline static bool IsKeyPressed(int keycode)		{ return s_Instance->IsKeyPressedPlatform(keycode); }
		inline static bool IsMouseButtonPressed(int button)	{ return s_Instance->IsMouseButtonPressedPlatform(button); }
		inline static std::pair<float, float> GetMousePos()	{ return s_Instance->GetMousePosPlatform(); }
		inline static float GetMouseX()						{ return s_Instance->GetMouseXPlatform(); }
		inline static float GetMouseY()						{ return s_Instance->GetMouseYPlatform(); }

		//TODO:ADD GAMEPAD CALLBACK

	protected:

		virtual bool IsKeyPressedPlatform(int keycode) = 0;
		virtual bool IsMouseButtonPressedPlatform(int button) = 0;
		virtual std::pair<float, float> GetMousePosPlatform() = 0;
		virtual float GetMouseXPlatform() = 0;
		virtual float GetMouseYPlatform() = 0;

	private:
		static Input* s_Instance;
	};
}