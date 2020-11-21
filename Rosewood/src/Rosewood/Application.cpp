#include "rwpch.h"
#include "Application.h"
#include "Rosewood/Log.h"
#include "Graphics/Graphics.h"
#include "Rosewood/Input/Input.h"
#include "Audio/Audio.h"



namespace Rosewood
{

#define BIND_EVENT_FUNCTION(x) std::bind(&x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;
	float Application::m_DeltaTime = 0.0f;
	float Application::m_Time = 0.0f;
	Application::Application()
	{
		RW_CORE_ASSERT(!s_Instance, "Why are you trying to make two applications? There is one already dumbass!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FUNCTION(Application::OnEvent));
        
		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

	}
	Application::~Application()
	{
	}
	void Application::Run()
	{
    
		float lateTime = 0;
        
        GraphicsCommand::Init();
        Audio::Init();


        while (m_Running)
		{

            m_Time = m_Window->GetTime();

			for (Layer* layer : m_LayerStack) {
				layer->OnUpdate();
			}

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack) 
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
			lateTime = m_Window->GetTime();
            m_DeltaTime = lateTime- m_Time;
		}
        Audio::Deinit();
	}
	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher = EventDispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNCTION(Application::OnWindowClosed));

		//RW_CORE_TRACE("{0}", e);

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
