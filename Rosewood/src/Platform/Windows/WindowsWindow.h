#pragma once

#include "Rosewood/Core/Window.h"

#include "Rosewood/Graphics/Graphics.h"

struct GLFWwindow;

namespace Rosewood {

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProperties& properties);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }
		inline float GetTime() override;

		inline void LockCursor() 	override;
		inline void UnlockCursor() 	override;
		//extend to cursor modes


		// Window attributes
		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
        virtual void SetTitle(const std::string& name) override;
		bool IsVSync() const override;
		void* GetWindowPtr() override { return m_Window; }
	private:
		virtual void Init(const WindowProperties& properties);
		virtual void Shutdown();
	private:
		GLFWwindow* m_Window;
        
        GraphicsContext* m_Context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};

}
