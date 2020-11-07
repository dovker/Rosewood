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
        virtual void OnLoad()   {};
        virtual void OnUpdate() {};
        virtual void OnDraw()   {};
        virtual void OnUnload() {};
    private:
        bool m_Visible;
    };
}
#endif
