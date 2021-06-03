#include "rwpch.h"

#include "wrap_Debug.h"

#include "Rosewood/Core/Log.h"
#include "Rosewood/Benchmark/Benchmark.h"

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

namespace Rosewood
{
    const char* wrap_Log::Name = "Log";

    luaL_Reg* wrap_Log::w_functions = 
        (luaL_Reg[]){
            {"Trace",    wrap_Log::w_trace},
            {"Assert",   wrap_Log::w_assert},
            {"Info",     wrap_Log::w_info},
            {"Warn",     wrap_Log::w_warn},
            {"Error",    wrap_Log::w_error},
            {"Critical", wrap_Log::w_critical}
        };

    int wrap_Log::functionCount = 6;
    int wrap_Log::metaFunctionCount = 0;

    int wrap_Log::w_trace(lua_State* L)
    {
        RW_LUA_TRACE(lua_tostring(L, -1));
        return 0;
    }

    int wrap_Log::w_assert(lua_State* L)
    {
        RW_ASSERT(lua_toboolean(L, -2), lua_tostring(L, -1));
        return 0;
    }// Wat

    int wrap_Log::w_info(lua_State* L)
    {
        RW_LUA_INFO(lua_tostring(L, -1));
        return 0;
    }

    int wrap_Log::w_warn(lua_State* L)
    {
        RW_LUA_WARN(lua_tostring(L, -1));
        return 0;
    }

    int wrap_Log::w_error(lua_State* L)
    {
        RW_LUA_ERROR(lua_tostring(L, -1));
        return 0;
    }
    
    int wrap_Log::w_critical(lua_State* L)
    {
        RW_LUA_CRITICAL(lua_tostring(L, -1));
        return 0;
    }


    const char* wrap_Benchmark::Name = "Benchmark";

    luaL_Reg* wrap_Benchmark::w_functions = 
        (luaL_Reg[]){
            {"Stop", wrap_Benchmark::w_stop},
            {"new",  wrap_Benchmark::w_create}
        };

    int wrap_Benchmark::functionCount = 2;

    const char* wrap_Benchmark::MetaName = "Benchmark_meta";

    luaL_Reg* wrap_Benchmark::w_metaFunctions = 
        (luaL_Reg[]){
            {"__gc",    wrap_Benchmark::w__gc},
            {"__index", wrap_Benchmark::w__index},
        };

    int wrap_Benchmark::metaFunctionCount = 2;

    int wrap_Benchmark::w_stop(lua_State* L)
    {
        BenchmarkTimer* timer = (BenchmarkTimer*)lua_touserdata(L, -1);
        timer->Stop();
        return 0;
    }

    int wrap_Benchmark::w_create(lua_State* L)
    {
        void* timer = (BenchmarkTimer*)lua_newuserdata(L, sizeof(BenchmarkTimer));
        new (timer) BenchmarkTimer(lua_tostring(L, -2));
        luaL_getmetatable(L, "Benchmark_meta");
        RW_CORE_ASSERT(lua_istable(L, -1), "META TABLE NOT FOUND");
        lua_setmetatable(L, -2);
        return 1;
    }

    int wrap_Benchmark::w__gc(lua_State* L)
    {
        BenchmarkTimer* timer = (BenchmarkTimer*)lua_touserdata(L, -1);
        timer->~BenchmarkTimer();
        return 0;
    }

    int wrap_Benchmark::w__index(lua_State* L)
    {
        const char* index = lua_tostring(L, -1);
        
        lua_getglobal(L, "Rosewood");
        lua_getfield(L, -1, "Benchmark");

        lua_pushstring(L, index);

        lua_rawget(L, -2);

        return 1;
    }
}