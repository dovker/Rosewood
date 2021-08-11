#pragma once
#include "Rosewood.h"
#include "../Map/Map.h"
#include <glm/glm.hpp>


namespace TestGame
{
    
    class Collision
    {
    public:
        static bool RectVsRect(Rosewood::Rect a, Rosewood::Rect b);
        static bool DynamicRectVsRect(Rosewood::Rect a, Rosewood::Rect b, glm::vec2 velocity, float deltaTime, glm::vec2& contactPoint, glm::vec2& contactNormal, float& contactTime);

        static bool Ray2DVsRect(Rosewood::Ray2D ray, Rosewood::Rect rect, glm::vec2& contactPoint, glm::vec2& contactNormal, float& hit_t);
        


    };
    
}
