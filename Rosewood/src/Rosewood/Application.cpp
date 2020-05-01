#include "rwpch.h"
#include "Application.h"
#include "Rosewood/Log.h"
#include "glad/glad.h"
#include "Rosewood/Input.h"


namespace Rosewood
{

#define BIND_EVENT_FUNCTION(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;
	Application::Application()
	{
		RW_CORE_ASSERT(!s_Instance, "Why are you trying to make two applications? There is one already dumbass!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FUNCTION(Application::OnEvent));

	}
	Application::~Application()
	{
	}
	void Application::Run()
	{
		

		while (m_Running)
		{
			glClearColor(1, 1, 0.5, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}

			RW_CORE_TRACE("{0}, {1}", Input::GetMouseX(), Input::GetMouseY());

			m_Window->OnUpdate();
		}
	}
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher = EventDispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNCTION(Application::OnWindowClosed));

		RW_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled) break;
		}
	}
	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}
	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}
	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}