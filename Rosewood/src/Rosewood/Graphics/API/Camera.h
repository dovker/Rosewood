#pragma once
#include <rwpch.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Rosewood
{
    class OrthographicCamera
	{
	public:
		OrthographicCamera() {}
		OrthographicCamera(float left, float right, float bottom, float top);

		void SetProjection(float left, float right, float bottom, float top);

		const glm::vec3& GetPosition() const { return m_Position; }
		void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

		float GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

		const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
        //const glm::mat4& GetProjectionViewMatrix() const { return m_ProjectionViewMatrix; }
	private:
		void RecalculateViewMatrix();
	private:
		glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
		glm::mat4 m_ViewMatrix = glm::mat4(1.0f);
		glm::mat4 m_ViewProjectionMatrix = glm::mat4(1.0f);
        //glm::mat4 m_ProjectionViewMatrix;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_Rotation = 0.0f;
		
	};
    class DecalCamera
    {
    public:
        DecalCamera() {}
        DecalCamera(float left, float right, float bottom, float top);

        void SetProjection(float left, float right, float bottom, float top);

        const glm::vec3& GetPosition() const { return m_Position; }
        void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }

        const glm::vec3& GetLookat() const { return m_Lookat; }
        void SetLookat(glm::vec3 lookat) { m_Lookat = lookat; RecalculateViewMatrix(); }

        const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
        const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
        const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }
        //const glm::mat4& GetProjectionViewMatrix() const { return m_ProjectionViewMatrix; }
    private:
        void RecalculateViewMatrix();
    private:
        glm::mat4 m_ProjectionMatrix = glm::mat4(1.0f);
        glm::mat4 m_ViewMatrix = glm::mat4(1.0f);
        glm::mat4 m_ViewProjectionMatrix = glm::mat4(1.0f);
        //glm::mat4 m_ProjectionViewMatrix;

        glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
        glm::vec3 m_Lookat = { 0.0f, 0.0f, 0.0f };
        
    };
}
