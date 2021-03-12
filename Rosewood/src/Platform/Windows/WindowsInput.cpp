#include "rwpch.h"
#include "WindowsInput.h"
#include "GLFW/glfw3.h"
#include "Rosewood/Core/Application.h"

namespace Rosewood
{

	bool Input::IsKeyPressed(int keycode)
	{
		auto window = (GLFWwindow*)Application::Get().GetWindow().GetWindowPtr();
		auto state = glfwGetKey(window, keycode);
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}

	bool Input::IsMouseButtonPressed(int button)
	{
		auto window = (GLFWwindow*)Application::Get().GetWindow().GetWindowPtr();
		auto state = glfwGetMouseButton(window, button);
		return state == GLFW_PRESS;
	}

	std::pair<float, float> Input::GetMousePos()
	{
		auto window = (GLFWwindow*)Application::Get().GetWindow().GetWindowPtr();
		double x, y;
		glfwGetCursorPos(window, &x, &y);
		return {(float)x, (float)y };
	}

	float Input::GetMouseX()
	{
		auto[x,y] = GetMousePos();
		return x;
	}

	float Input::GetMouseY()
	{
		auto [x, y] = GetMousePos();
		return y;
	}

}

