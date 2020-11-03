#include "Entity.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#ifndef Player_h
#define Player_h

public class Player : Entity
{
public:
    Entity();
    ~Entity();
    virtual void Load() override;
    virtual void Update() override;
    virtual void Draw() override;
private:
    
}

#endif /* Player_h */
