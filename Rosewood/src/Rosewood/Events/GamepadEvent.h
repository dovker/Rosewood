#pragma once

#include "Event.h"



namespace Rosewood {
	

	class GamepadEvent : public Event
	{
	public:
		inline int GetGamepadButton() const { return m_Button; }

		EVENT_CLASS_CATEGORY(EventCategoryGamepad | EventCategoryGamepadButton |  EventCategoryInput)
	protected:
		GamepadEvent(int button)
			: m_Button(button) {}

		int m_Button;
	};

	class GamepadPressedEvent : public GamepadEvent
	{
	public:
		GamepadPressedEvent(int button)
			: GamepadEvent(button) {}


		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "GamepadPressedEvent: " << (int)m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(GamepadButtonPressed)
	
	};

	class GamepadReleasedEvent : public GamepadEvent
	{
	public:
		GamepadReleasedEvent(int button)
			: GamepadEvent(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "GamepadReleasedEvent: " << (int)m_Button;
			return ss.str();
		}

		EVENT_CLASS_TYPE(GamepadButtonReleased)
	};

	class GamepadAxisMovedEvent : public Event
	{
	public:
		GamepadAxisMovedEvent(int axis, float value)
			: m_Axis(axis), m_AxisValue(value){}

		inline int GetGamepadAxis() const { return m_Axis; }
		inline float GetValue() const { return m_AxisValue; }
		

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "GamepadAxisMovedEvent: " << (int)m_Axis << " - " << m_AxisValue;
			return ss.str();
		}

		EVENT_CLASS_TYPE(GamepadAxisMoved)
		EVENT_CLASS_CATEGORY(EventCategoryGamepad | EventCategoryGamepadAxis | EventCategoryInput)
	private:
		int m_Axis;
		float m_AxisValue;
	};
}