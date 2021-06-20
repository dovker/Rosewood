#pragma once
#include "rwpch.h"

struct luaL_Reg;
struct lua_State;

namespace Rosewood
{
    class LuaWrapper
    {
    public:
        LuaWrapper() {};

        virtual const char* GetName() const = 0;
    };
}