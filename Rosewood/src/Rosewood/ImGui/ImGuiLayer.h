#pragma once

#include "Rosewood/Layer.h"
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

		void Begin();
		void End();


	private:
		float m_Time = 0.0f;

	};

}
