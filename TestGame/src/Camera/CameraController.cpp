#include "CameraController.h"

namespace TestGame
{


    Rosewood::OrthographicCamera Camera::GetCamera()
    {
        return m_Camera;
    }

    void Camera::ProcessMouseScroll(float yoffset)
    {
        
        m_Zoom -= yoffset;
                
        m_Camera.SetProjection(0, m_ScrSize.x / m_Zoom, m_ScrSize.y / m_Zoom, 0);
    }
    void Camera::OnEvent(Rosewood::Event &e)
    {
        Rosewood::EventDispatcher dispatcher(e);
        dispatcher.Dispatch<Rosewood::WindowResizeEvent>(RW_BIND_EVENT_FN(Camera::ProcessScreenResize));

    }
    void Camera::SetPosition(glm::vec2 pos)
    {
        m_Position = pos;
        m_Camera.SetPosition(glm::vec3(pos, 0.0f));

    }
    bool Camera::ProcessScreenResize(Rosewood::WindowResizeEvent& e)
    {
        uint32_t x = e.GetWidth();
        uint32_t y = e.GetHeight();
        m_Camera.SetProjection(0, x / m_Zoom, y / m_Zoom, 0); // Change Application window size
        Rosewood::GraphicsCommand::SetViewport(0, 0, x, y);
        return false;
    }
    glm::vec2 Camera::GetWorldCoords(glm::vec2 pos)
    {
        glm::vec4 vec = glm::vec4(pos, 0.0f, 0.0f) * glm::inverse(m_Camera.GetViewProjection());
        return {vec.x, vec.y};
    }

    void Camera::OnUpdate(float dt)
    {
        m_Position.x = glm::mix(m_Position.x, m_Target->GetPosition().x - 1280.0f/2/4 + m_Target->GetSprite()->Texture->GetWidth()/2, dt*10.0f);
        m_Position.y = glm::mix(m_Position.y, m_Target->GetPosition().y - 720.0f/2/4 + m_Target->GetSprite()->Texture->GetHeight()/2, dt*10.0f);
        m_Camera.SetPosition(glm::vec3(m_Position, 0.0f));

    }

}
