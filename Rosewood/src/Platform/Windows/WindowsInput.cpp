#include "rwpch.h"
#include "WindowsInput.h"
#include "GLFW/glfw3.h"
#include "Rosewood/Application.h"

namespace Rosewood
{
	Input* Input::s_Instance = new WindowsInput();

	bool WindowsInput::IsKeyPressedPlatform(int keycode)
	{
		auto window = (GLFWwindow*)Application::Get().GetWindow().GetWindowPtr();
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool WindowsInput::IsMouseButtonPressedPlatform(int button)
	{
		auto window = (GLFWwindow*)Application::Get().GetWindow().GetWindowPtr();
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> WindowsInput::GetMousePosPlatform()
	{
		auto window = (GLFWwindow*)Application::Get().GetWindow().GetWindowPtr();
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return {(float)x, (float)y };
	}

	float WindowsInput::GetMouseXPlatform()
	{
		auto[x,y] = GetMousePosPlatform();
		return x;
	}

	float WindowsInput::GetMouseYPlatform()
	{
		auto [x, y] = GetMousePosPlatform();
		return y;
	}

}

