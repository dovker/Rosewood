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
#include "sol/sol.hpp"


namespace Rosewood
{
    const char* wrap_Log::Name = "Log";
    wrap_Log::wrap_Log(lua_State* L)
    {
        sol::state_view lua(L);

        auto ns = lua["Rosewood"].get_or_create<sol::table>();

        auto table = lua.create_table_with(
            "Trace",    w_trace  ,
            "Assert",   w_assert ,
            "Info",     w_info   ,
            "Warn",     w_warn   ,
            "Error",    w_error  ,
            "Critical", w_critical
        );
        ns["Log"] = table;
    }

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

    wrap_Benchmark::wrap_Benchmark(lua_State* L)
    {
        sol::state_view lua(L);

        auto ns = lua["Rosewood"].get_or_create<sol::table>();

        ns.new_usertype<BenchmarkTimer>("BenchmarkTimer",
            sol::constructors<BenchmarkTimer(const std::string&)>(),
            "Stop", &BenchmarkTimer::Stop
        );
    }
}