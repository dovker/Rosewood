#pragma once
#include "Rosewood.h"
#include "Entity.h"
#include <glm/glm.hpp>


namespace TestGame
{
    class Collider
    {
    public:
        Collider() {};
        glm::vec2 Position;
    };
    class AABB : public Collider
    {
    public:
        glm::vec2 Position;
        glm::vec2 Size;
        
        AABB(glm::vec2 pos, glm::vec2 pos2)
        : Position(pos), Size(pos2)
        {}
        AABB() {};
    };
    class Collision
    {
    public:
        static bool Check(AABB &a, AABB &b);
    };
    
}
