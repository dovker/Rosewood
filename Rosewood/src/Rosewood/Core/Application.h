#pragma once

#include "rwpch.h"

#include "Core.h"
#include "Rosewood/Events/Event.h"
#include "Rosewood/Events/EventPool.h"
#include <Rosewood/Events/ApplicationEvent.h>
#include <Rosewood/Core/Window.h>
#include <Rosewood/Core/Layer.h>
#include <Rosewood/Core/LayerStack.h>
#include <Rosewood/ImGui/ImGuiLayer.h>
#include <Rosewood/Core/Timestep.h>


namespace Rosewood
{
	class  Application
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
		
		inline static float GetTime() { return m_Time;  };
        inline static float GetDeltaTime() { return m_DeltaTime;  };

	private:
		bool OnWindowClosed(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;
		//EventPool m_EventPool;

	private:
		static Application* s_Instance;
		static float m_Time;
        static float m_DeltaTime;

        float m_LastFrameTime = 0.0f;

	};

	//Has to be defined in CLIENT
	Application* CreateApplication();
}
