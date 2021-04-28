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
    class wrap_Application : public LuaWrapper
    {
    private:


        const char* Name = "Application";
        luaL_Reg* w_functions = 
        (luaL_Reg[]){
            {"GetDeltaTime", w_getDeltaTime},
            {"GetDeltaTimeMiliseconds", w_getDeltaTimeMiliseconds},
            {"GetTime", w_getTime},
            {"GetTimeMiliseconds", w_getTimeMiliseconds},

        };
        int functionCount = 4; 
    
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

        const char* Name = "Window";
        luaL_Reg* w_functions = 
        (luaL_Reg[]){
            {"SetTitle", w_setTitle},
            {"GetWidth", w_getWidth},
            {"GetHeight", w_getHeight}
        };
        int functionCount = 3;
    
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