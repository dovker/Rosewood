#pragma once

#include "rwpch.h"

#include "Core.h"
#include "Events/Event.h"
#include <Rosewood\Events\ApplicationEvent.h>
#include <Rosewood\Window.h>
#include <Rosewood\Layer.h>
#include <Rosewood\LayerStack.h>


namespace Rosewood
{
	class ROSEWOOD_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);
		
		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance;  }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClosed(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

	private:
		static Application* s_Instance;
	};

	//Has to be defined in CLIENT
	Application* CreateApplication();
}
