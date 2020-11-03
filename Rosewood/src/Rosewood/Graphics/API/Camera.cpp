  
#include "rwpch.h"
#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace Rosewood {

	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, 10000.0f, -10000.0f)), m_ViewMatrix(1.0f)
	{
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
	{
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, 10000.0f, -10000.0f);
		
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
//		glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
//			glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(1, 0, 0));
//
//
//		m_ViewMatrix = glm::inverse(transform);
        glm::mat4 rot = glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 1, 0));
        
        m_ViewMatrix = rot * glm::lookAt(m_Position, m_Position + glm::normalize(glm::vec3(0.0f, 0.0f, -1.0f)), glm::vec3(0.0f, 1.0f, 0.0f));
        
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

    DecalCamera::DecalCamera(float left, float right, float bottom, float top)
        : m_ProjectionMatrix(glm::ortho(left, right, bottom, top, 10000.0f, -10000.0f)), m_ViewMatrix(1.0f)
    {
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

    void DecalCamera::SetProjection(float left, float right, float bottom, float top)
    {
        m_ProjectionMatrix = glm::ortho(left, right, bottom, top, 10000.0f, -10000.0f);
        
    }

    void DecalCamera::RecalculateViewMatrix()
    {
                  
        m_ViewMatrix = glm::lookAt(m_Position, m_Lookat, glm::vec3(0.0f, 1.0f, 0.0f));
        
        m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
    }

}
