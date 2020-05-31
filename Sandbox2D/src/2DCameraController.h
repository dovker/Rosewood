#include <Rosewood.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
//#include "glad/glad.h"

const float SPEED = 50.0f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 1.0f;


class Camera
{
public:
    
    /*Camera(float aspect_ratio) :  m_MovementSpeed(SPEED), m_Zoom(ZOOM), m_AspectRatio(aspect_ratio),
        m_Camera(Rosewood::OrthographicCamera(-m_AspectRatio * m_Zoom, m_AspectRatio* m_Zoom, -m_Zoom, m_Zoom))
    {
        m_Position = camera.GetPosition();
    }*/
    Camera(glm::vec2 scrSize) : m_MovementSpeed(SPEED), m_Zoom(ZOOM), m_ScrSize(scrSize),
        m_Camera(Rosewood::OrthographicCamera(0, m_ScrSize.x / m_Zoom, m_ScrSize.y / m_Zoom, 0))
    {
        m_Position = m_Camera.GetPosition();
    }

    Rosewood::OrthographicCamera GetCamera()
    {
        return m_Camera;
    }
    void ProcessKeyboard(float deltaTime)
    {
        float cameraSpeed = m_MovementSpeed * deltaTime; // adjust accordingly
        if (Rosewood::Input::IsKeyPressed(KEY_W))
            m_Position.y -= cameraSpeed;
        if (Rosewood::Input::IsKeyPressed(KEY_S))
            m_Position.y += cameraSpeed;
        if (Rosewood::Input::IsKeyPressed(KEY_A))
            m_Position.x -= cameraSpeed;
        if (Rosewood::Input::IsKeyPressed(KEY_D))
            m_Position.x += cameraSpeed;
        
        
        m_Camera.SetPosition(m_Position);
    }

    // Processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
    void ProcessMouseScroll(float yoffset)
    {
        
        m_Zoom -= yoffset;
        
        //m_Camera.SetProjection(-m_AspectRatio * m_Zoom, m_AspectRatio * m_Zoom, -m_Zoom, m_Zoom);
        
        m_Camera.SetProjection(0, m_ScrSize.x / m_Zoom, m_ScrSize.y / m_Zoom, 0);
    }
private:
    glm::vec3 m_Position;
    // Camera options
    float m_MovementSpeed;
    float m_Zoom = 1.0f;
    float m_AspectRatio;
    glm::vec2 m_ScrSize;
    Rosewood::OrthographicCamera m_Camera;
};
