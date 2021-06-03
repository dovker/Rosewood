#pragma once
#include "rwpch.h"

struct luaL_Reg;

namespace Rosewood
{
    class LuaWrapper
    {
    public:
        LuaWrapper() {}

        virtual const char* GetName() const = 0;
        virtual const char* GetMetaName() const = 0;
        virtual int GetMetaFunctionCount() const = 0;
        virtual int GetFunctionCount() const = 0;
        virtual luaL_Reg* GetMetafunctions() const = 0;
        virtual luaL_Reg* GetFunctions() const = 0;
    };
}