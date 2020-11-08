#include "Rosewood.h"

#ifndef Entity_h
#define Entity_h

namespace TestGame
{
    class Entity
    {
    public:
        Entity(){};
        ~Entity(){};
        virtual void OnLoad() = 0;
        virtual void OnUpdate() = 0;
        virtual void OnDraw() = 0;
        virtual void OnUnload() = 0;
    private:
        bool m_Visible;
    };
}
#endif
