#pragma once

#include "wrapper.h"


struct luaL_Reg;
struct lua_State;

namespace Rosewood
{
    class wrap_Log : public LuaWrapper
    {
    private:
        static const char* Name;
    
    public:
        static int w_trace(lua_State* L);
        static int w_assert(lua_State* L);
        static int w_info(lua_State* L);
        static int w_warn(lua_State* L);
        static int w_error(lua_State* L);
        static int w_critical(lua_State* L);

        wrap_Log(lua_State* L);
        virtual const char* GetName() const { return Name; }
    };

    class wrap_Benchmark : public LuaWrapper
    {
    private:
        static const char* Name;    
    public:
        wrap_Benchmark(lua_State* L);
        virtual const char* GetName() const { return Name; }

    };
}