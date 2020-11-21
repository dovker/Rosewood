#pragma once
#include "Rosewood.h"

namespace TestGame
{
    class Camera
    {
        public:
            Camera(glm::vec2 scrSize) : m_Zoom(1.0f), m_ScrSize(scrSize), m_Position(glm::vec3(0.0f, 0.0f, 0.0f)),
                m_Camera(Rosewood::OrthographicCamera(0, m_ScrSize.x / m_Zoom, m_ScrSize.y / m_Zoom, 0))
            {
                
            }

            Rosewood::OrthographicCamera GetCamera()
            {
                return m_Camera;
            }

            void ProcessMouseScroll(float yoffset)
            {
                
                m_Zoom -= yoffset;
                        
                m_Camera.SetProjection(0, m_ScrSize.x / m_Zoom, m_ScrSize.y / m_Zoom, 0);
            }
            void OnEvent(Rosewood::Event &e)
            {
                Rosewood::EventDispatcher dispatcher(e);
                dispatcher.Dispatch<Rosewood::WindowResizeEvent>(RW_BIND_EVENT_FN(Camera::ProcessScreenResize));

            }
            void SetPosition(glm::vec3 pos)
            {
                m_Position = pos;
                m_Camera.SetPosition(pos);

            }
            bool ProcessScreenResize(Rosewood::WindowResizeEvent& e)
            {
                uint32_t x = e.GetWidth();
                uint32_t y = e.GetHeight();
                m_Camera.SetProjection(0, x / m_Zoom, y / m_Zoom, 0); // Change Application window size
                Rosewood::GraphicsCommand::SetViewport(0, 0, x, y);
                return false;
            }

        private:
            glm::vec3 m_Position;
            // Camera options
            float m_Zoom = 1.0f;
            float m_Rotation = 0.0f;
            glm::vec2 m_ScrSize;
            Rosewood::OrthographicCamera m_Camera;
    };

}
