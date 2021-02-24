#pragma once
#include "Rosewood.h"
#include <glm/glm.hpp>


namespace TestGame
{
    
    class Collision
    {
    public:
        static bool Check(Rosewood::Rect a, Rosewood::Rect b);
    };
    
}
