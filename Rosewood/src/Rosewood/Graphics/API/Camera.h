#pragma once
#include <rwpch.h>
#include "Rosewood/Events/Event.h"
#include "Rosewood/Events/MouseEvent.h"
#include "Rosewood/Events/KeyEvent.h"
#include "Rosewood/Events/ApplicationEvent.h"
#include "Rosewood/Core/Timestep.h"


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Rosewood
{
    class Camera
    {
    public:
        Camera() = default;
        Camera(const glm::mat4& projection)
            : m_Projection(projection) {}

        virtual ~Camera() = default;

        const glm::mat4& GetProjection() const { return m_Projection; }
    protected:
        glm::mat4 m_Projection = glm::mat4(1.0f);
    };

    class EditorCamera : public Camera
    {
    public:
        EditorCamera() = default;
        EditorCamera(float fov, float aspectRatio, float nearClip, float farClip);

        void OnUpdate(Timestep ts);
        void OnEvent(Event& e);

        inline float GetDistance() const { return m_Distance; }
        inline void SetDistance(float distance) { m_Distance = distance; }

        inline void SetViewportSize(float width, float height) { m_ViewportWidth = width; m_ViewportHeight = height; UpdateProjection(); }

        const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
        glm::mat4 GetViewProjection() const { return m_Projection * m_ViewMatrix; }

        glm::vec3 GetUpDirection() const;
        glm::vec3 GetRightDirection() const;
        glm::vec3 GetForwardDirection() const;
        const glm::vec3& GetPosition() const { return m_Position; }
        glm::quat GetOrientation() const;

        float GetPitch() const { return m_Pitch; }
        float GetYaw() const { return m_Yaw; }
    private:
        void UpdateProjection();
        void UpdateView();

        bool OnMouseScroll(MouseScrolledEvent& e);

        void MousePan(const glm::vec2& delta);
        void MouseRotate(const glm::vec2& delta);
        void MouseZoom(float delta);

        glm::vec3 CalculatePosition() const;

        std::pair<float, float> PanSpeed() const;
        float RotationSpeed() const;
        float ZoomSpeed() const;
    private:
        float m_FOV = 45.0f, m_AspectRatio = 1.778f, m_NearClip = 0.1f, m_FarClip = 1000.0f;

        glm::mat4 m_ViewMatrix;
        glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
        glm::vec3 m_FocalPoint = { 0.0f, 0.0f, 0.0f };

        glm::vec2 m_InitialMousePosition = { 0.0f, 0.0f };

        float m_Distance = 10.0f;
        float m_Pitch = 0.0f, m_Yaw = 0.0f;

        float m_ViewportWidth = 1280, m_ViewportHeight = 720;
    };
    class OrthographicCamera : public Camera
    {
    public:
            OrthographicCamera() {}
            OrthographicCamera(float left, float right, float bottom, float top);

            void SetProjection(float left, float right, float bottom, float top);

            const glm::vec3& GetPosition() const { return m_Position; }
            void SetPosition(const glm::vec3& position) { m_Position = position; RecalculateViewMatrix(); }
            void SetZoom(const float& zoom) { m_Zoom = zoom; RecalculateViewMatrix(); }

            float GetRotation() const { return m_Rotation; }
            void SetRotation(float rotation) { m_Rotation = rotation; RecalculateViewMatrix(); }

            const glm::mat4& GetProjection() const { return m_Projection; }
            const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
            glm::mat4 GetViewProjection() const { return m_Projection * m_ViewMatrix; }
        private:
            void RecalculateViewMatrix();
        private:
            glm::mat4 m_ViewMatrix = glm::mat4(1.0f);

            glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
            float m_Rotation = 0.0f;
            float m_Zoom = 1.0f;
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
