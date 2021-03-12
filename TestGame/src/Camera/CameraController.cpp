#include "CameraController.h"

namespace TestGame
{


    Rosewood::OrthographicCamera GameCamera::GetCamera()
    {
        return m_Camera;
    }

    bool GameCamera::ProcessMouseScroll(Rosewood::MouseScrolledEvent& e)
    {   
        m_TargetZoom = glm::clamp(m_TargetZoom + e.GetYOffset(), 0.5f, 10.0f);
        return false;
    }
    void GameCamera::OnEvent(Rosewood::Event &e)
    {
        Rosewood::EventDispatcher dispatcher(e);
        dispatcher.Dispatch<Rosewood::WindowResizeEvent>(RW_BIND_EVENT_FN(GameCamera::ProcessScreenResize));
        dispatcher.Dispatch<Rosewood::MouseScrolledEvent>(RW_BIND_EVENT_FN(GameCamera::ProcessMouseScroll));

    }
    void GameCamera::SetPosition(glm::vec2 pos)
    {
        m_Position = pos;
        UpdateCamera();
    }
    void GameCamera::SetZoom(float zoom)
    {
        m_Zoom = zoom;
        UpdateCamera();
    }
    bool GameCamera::ProcessScreenResize(Rosewood::WindowResizeEvent& e)
    {
        m_ScrSize.x = e.GetWidth();
        m_ScrSize.y = e.GetHeight();
        #ifdef RW_PLATFORM_MACOS
        m_ScrSize /= 2.0f;
        #endif
        //Rosewood::GraphicsCommand::SetViewport(0, 0, m_ScrSize.x, m_ScrSize.y);
        m_Camera.SetProjection(-m_ScrSize.x/2.0f, m_ScrSize.x/2.0f, m_ScrSize.y/2.0f, -m_ScrSize.y/2.0);        
        return false;
    }
    glm::vec2 GameCamera::ScreenToWorldCoords(glm::vec2 pos)
    {
        glm::vec2 p = {pos.x, pos.y};

        p /= m_ScrSize; // Range from 0f to 1f
        p.y = 1.0f - p.y; // Inverting y
        p = (p-0.5f)*2.0f; // Range NDC Range
        glm::vec4 vec = glm::inverse(m_Camera.GetViewProjection()) * glm::vec4(p, 1.0f, 1.0f) ; // NDC to World Space
        return {vec.x, vec.y}; //World space
    }


    void GameCamera::OnUpdate(float dt)
    {
        m_Position.x = glm::mix(m_Position.x, m_Target->GetPosition().x + m_Target->GetBounds().Width/2, dt*10.0f);
        m_Position.y = glm::mix(m_Position.y, m_Target->GetPosition().y + m_Target->GetBounds().Height/2, dt*10.0f);
        m_Zoom = (glm::mix(m_Zoom, m_TargetZoom, dt*10.0f));
        UpdateCamera();
    }
    void GameCamera::UpdateCamera()
    {
        m_Camera.SetPosition(glm::vec3(m_Position , 0.0f));
        m_Camera.SetZoom(m_Zoom);
        m_Bounds = Rosewood::Rect(m_Position - (glm::vec2(m_ScrSize.x / m_Zoom, m_ScrSize.y / m_Zoom)/2.0f), glm::vec2(m_ScrSize.x / m_Zoom, m_ScrSize.y / m_Zoom));
    }

}
