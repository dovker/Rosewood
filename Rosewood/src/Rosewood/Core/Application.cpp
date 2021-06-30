#include "rwpch.h"
#include "Application.h"
#include "Rosewood/Graphics/Graphics.h"
#include "Rosewood/Input/Input.h"
#include "Rosewood/Audio/Audio.h"



namespace Rosewood
{

	Application* Application::s_Instance = nullptr;
	float Application::m_Time = 0.0f;
    float Application::m_DeltaTime = 0.0f;

	Application::Application()
	{
		RW_CORE_ASSERT(!s_Instance, "Why are you trying to make two applications? There is one already dumbass!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(RW_BIND_EVENT_FN(Application::OnEvent));
        
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

	}
	Application::~Application()
	{
	}
	void Application::Run()
	{
            
        GraphicsCommand::Init();
        Audio::Init();
        

        while (m_Running)
		{
            m_Time = m_Window->GetTime();
            Timestep timestep = m_Time - m_LastFrameTime;
            m_LastFrameTime = m_Time;
            m_DeltaTime = timestep;

			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate(timestep);
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack) 
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
        Audio::Deinit();
	}
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher = EventDispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(RW_BIND_EVENT_FN(Application::OnWindowClosed));

		//RW_CORE_TRACE("{0}", e);

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			if (e.Handled) break;
			(*--it)->OnEvent(e);
		}
	}
	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}
	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
	}
	
	bool Application::OnWindowClosed(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
}
