#include <Rosewood.h>

#ifndef Entity_h
#define Entity_h

public class Entity
{
public:
    Entity();
    ~Entity();
    virtual void Load();
    virtual void Update();
    virtual void Draw();
}

#endif /* Entity_h */
