#pragma once

#include "Rosewood/Layer.h"
#include "Rosewood/Events/Event.h"
#include <Rosewood\Events\KeyEvent.h>
#include <Rosewood\Events\MouseEvent.h>
#include <Rosewood\Events\ApplicationEvent.h>

namespace Rosewood {

	class ROSEWOOD_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void OnAttach();
		
		void OnDetach();

		void OnUpdate();
		void OnEvent(Event& event);


	private:
		float m_Time = 0.0f;

		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);
		
	};

}