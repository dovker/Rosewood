#pragma once
#include "Rosewood.h"
#include "../Entity/Entity.h"

namespace TestGame
{
    class GameCamera
    {
        public:
            GameCamera(glm::vec2 scrSize) : m_Zoom(1.0f), m_ScrSize(scrSize), m_Position(glm::vec3(0.0f, 0.0f, 0.0f)),
                m_Camera(Rosewood::OrthographicCamera(-m_ScrSize.x/2.0f, m_ScrSize.x/2.0f, m_ScrSize.y/2.0f, -m_ScrSize.y/2.0)), m_Bounds(Rosewood::Rect(m_Position - (glm::vec2(m_ScrSize.x / m_Zoom, m_ScrSize.y / m_Zoom)/2.0f), glm::vec2(m_ScrSize.x / m_Zoom, m_ScrSize.y / m_Zoom)))
                {}

            Rosewood::OrthographicCamera GetCamera();

            bool ProcessMouseScroll(Rosewood::MouseScrolledEvent& e);
            void OnUpdate(float dt);
            void OnEvent(Rosewood::Event &e);
            void SetPosition(glm::vec2 pos);
            void SetZoom(float zoom);
            bool ProcessScreenResize(Rosewood::WindowResizeEvent& e);

            glm::vec2 ScreenToWorldCoords(glm::vec2 pos);
            void SetTarget(Entity* entity) {m_Target = entity;};
            Rosewood::Rect GetBounds() {return m_Bounds;}

        private:
            glm::vec2 m_Position;
            Entity* m_Target;
            // Camera options
            float m_TargetZoom = 1.0f;
            float m_Zoom = 1.0f;
            float m_Rotation = 0.0f;
            glm::vec2 m_ScrSize;
            Rosewood::OrthographicCamera m_Camera;
            Rosewood::Rect m_Bounds;
            void UpdateCamera();
    };

}
