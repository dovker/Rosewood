#pragma once
#include "Game.h"

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
        void ProcessScreenResize(glm::vec2 scrSize)
        {
            m_Camera.SetProjection(0, scrSize.x / m_Zoom, scrSize.y / m_Zoom, 0);
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
