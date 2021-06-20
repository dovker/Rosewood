#pragma once

#include "wrapper.h"

struct luaL_Reg;
struct lua_State;

namespace Rosewood
{
    
    class wrap_Input : public LuaWrapper
    {
    private:
        static const char* Name;
    
    public:
        static int w_isKeyPressed(lua_State* L);
        static int w_isMouseButtonPressed(lua_State* L);

        wrap_Input(lua_State* L);
        virtual const char* GetName() const { return Name; }
    };
}