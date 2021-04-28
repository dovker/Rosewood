#include "rwpch.h"

#include "wrap_Debug.h"

#include "Rosewood/Core/Log.h"
#include "Rosewood/Benchmark/Benchmark.h"


namespace Rosewood
{
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