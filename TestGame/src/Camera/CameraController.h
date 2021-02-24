#pragma once
#include "Rosewood.h"
#include "../Collision/Collision.h"
#include "../Entity/Entity.h"

namespace TestGame
{
    class Camera
    {
        public:
            Camera(glm::vec2 scrSize) : m_Zoom(1.0f), m_ScrSize(scrSize), m_Position(glm::vec3(0.0f, 0.0f, 0.0f)),
                m_Camera(Rosewood::OrthographicCamera(0, m_ScrSize.x / m_Zoom, m_ScrSize.y / m_Zoom, 0))
                {}

            Rosewood::OrthographicCamera GetCamera();

            void ProcessMouseScroll(float yoffset);
            void OnUpdate(float dt);
            void OnEvent(Rosewood::Event &e);
            void SetPosition(glm::vec2 pos);
            bool ProcessScreenResize(Rosewood::WindowResizeEvent& e);

            glm::vec2 GetWorldCoords(glm::vec2 pos);
            void SetTarget(Entity* entity) {m_Target = entity;};
            Rosewood::Rect GetBounds();

        private:
            glm::vec2 m_Position;
            Entity* m_Target;
            // Camera options
            float m_Zoom = 1.0f;
            float m_Rotation = 0.0f;
            glm::vec2 m_ScrSize;
            Rosewood::OrthographicCamera m_Camera;
    };

}
