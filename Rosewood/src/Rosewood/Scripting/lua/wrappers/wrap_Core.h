#pragma once

#include "wrapper.h"



struct luaL_Reg;
struct lua_State;


namespace Rosewood
{
    
    class wrap_Application : public LuaWrapper
    {
    private:


        static const char* Name;
        static luaL_Reg* w_functions;
        static int functionCount; 
    
    public:
        static int w_getDeltaTime(lua_State* L);
        static int w_getDeltaTimeMiliseconds(lua_State* L);
        static int w_getTime(lua_State* L);
        static int w_getTimeMiliseconds(lua_State* L);

        wrap_Application() {}
        virtual const char* GetName() const { return Name; }
        virtual const char* GetMetaName() const { return ""; }
        virtual int GetMetaFunctionCount() const { return 0; }
        virtual int GetFunctionCount() const { return functionCount; }
        virtual luaL_Reg* GetMetafunctions() const { return nullptr; }
        virtual luaL_Reg* GetFunctions() const { return w_functions; }

    };

    class wrap_Window : public LuaWrapper
    {
    private:

        static const char* Name;
        static luaL_Reg* w_functions;
        static int functionCount;
    
    public:
        static int w_setTitle(lua_State* L);
        static int w_getWidth(lua_State* L);
        static int w_getHeight(lua_State* L);

        wrap_Window() {}
        virtual const char* GetName() const { return Name; }
        virtual const char* GetMetaName() const { return ""; }
        virtual int GetMetaFunctionCount() const { return 0; }
        virtual int GetFunctionCount() const { return functionCount; }
        virtual luaL_Reg* GetMetafunctions() const { return nullptr; }
        virtual luaL_Reg* GetFunctions() const { return w_functions; }

    };
}