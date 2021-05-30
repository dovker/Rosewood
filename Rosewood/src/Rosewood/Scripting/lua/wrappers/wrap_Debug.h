#pragma once

#include "wrapper.h"

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

namespace Rosewood
{
    class wrap_Log : public LuaWrapper
    {
    private:


        const char* Name = "Log";

        luaL_Reg* w_functions = 
        (luaL_Reg[]){
            {"Trace", w_trace},
            {"Assert", w_assert},
            {"Info", w_info},
            {"Warn", w_warn},
            {"Error", w_error},
            {"Critical", w_critical}
        };
        int functionCount = 6;
        int metaFunctionCount = 0;
    
    public:
        static int w_trace(lua_State* L);
        static int w_assert(lua_State* L);
        static int w_info(lua_State* L);
        static int w_warn(lua_State* L);
        static int w_error(lua_State* L);
        static int w_critical(lua_State* L);

        wrap_Log() {}
        virtual const char* GetName() const { return Name; }
        virtual const char* GetMetaName() const { return ""; }
        virtual int GetMetaFunctionCount() const { return metaFunctionCount; }
        virtual int GetFunctionCount() const { return functionCount; }
        virtual luaL_Reg* GetMetafunctions() const { return nullptr; }
        virtual luaL_Reg* GetFunctions() const { return w_functions; }

    };

    class wrap_Benchmark : public LuaWrapper
    {
    private:


        const char* Name = "Benchmark";
        const char* MetaName = "Benchmark_meta";
        luaL_Reg* w_functions = 
        (luaL_Reg[]){
            {"Stop", w_stop},
            {"new", w_create}
        };
        luaL_Reg* w_metaFunctions = 
        (luaL_Reg[]){
            {"__gc", w__gc},
            {"__index", w__index},
        };
        int functionCount = 2;
        int metaFunctionCount = 2;
    
    public:
        
        static int w_stop(lua_State* L);
        static int w_create(lua_State* L);
        static int w__gc(lua_State* L);
        static int w__index(lua_State* L);

        wrap_Benchmark() {}
        virtual const char* GetName() const { return Name; }
        virtual const char* GetMetaName() const { return MetaName; }
        virtual int GetMetaFunctionCount() const { return metaFunctionCount; }
        virtual int GetFunctionCount() const { return functionCount; }
        virtual luaL_Reg* GetMetafunctions() const { return w_metaFunctions; }
        virtual luaL_Reg* GetFunctions() const { return w_functions; }

    };
}