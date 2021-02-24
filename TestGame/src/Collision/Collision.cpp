#include "Collision.h"

namespace TestGame
{
    bool Collision::Check(Rosewood::Rect a, Rosewood::Rect b)
    {
        return
        a.Left < b.Right &&
        a.Right > b.Left &&
        a.Bottom > b.Top &&
        a.Top < b.Bottom;
    }
}
