#include "Collision.h"

namespace TestGame
{
    bool Collision::Check(AABB &a, AABB &b)
    {
        return
        a.Position.x + a.Size.x > b.Position.x &&
        a.Position.x < b.Position.x + b.Size.x &&
        a.Position.y < b.Position.y + b.Size.y &&
        a.Position.y + a.Size.y > b.Position.y;
    }
}
