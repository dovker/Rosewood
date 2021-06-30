#pragma once

#include "wrapper.h"

struct luaL_Reg;
struct lua_State;

namespace Rosewood
{
    
    class wrap_ECS : public LuaWrapper
    {
    private:
        static const char* Name;
    
    public:
        wrap_ECS(lua_State* L);
        virtual const char* GetName() const { return Name; }
    };
}