#include "Rosewood.h"
#include "Entity.h"
#include "glm/glm.hpp"

#ifndef Player_h
#define Player_h
namespace TestGame
{
    class Player : public Entity
    {
    public:
        Player();
        ~Player();
        void OnLoad() override;
        void OnUpdate() override;
        void OnDraw() override;
        void OnUnload() override;

    private:
        glm::vec3 m_Position;
    };
}
#endif /* Player_h */
