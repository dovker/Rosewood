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
        static luaL_Reg* w_functions;
        static int functionCount;
        static int metaFunctionCount;
    
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
        static const char* Name;
        static const char* MetaName;
        static luaL_Reg* w_functions;
        static luaL_Reg* w_metaFunctions;
        static int functionCount;
        static int metaFunctionCount;
    
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