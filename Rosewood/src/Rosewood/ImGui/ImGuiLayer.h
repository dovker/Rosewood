#pragma once

#include "Rosewood/Core/Layer.h"
#include "Rosewood/Events/Event.h"
#include <Rosewood/Events/KeyEvent.h>
#include <Rosewood/Events/MouseEvent.h>
#include <Rosewood/Events/ApplicationEvent.h>

namespace Rosewood {

	class  ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		virtual void OnEvent(Event& e) override;
		
		void SetEventBlocking(bool blocking) { m_BlockEvents = blocking; }

		void Begin();
		void End();


	private:
		bool m_BlockEvents = true;
	};

}
