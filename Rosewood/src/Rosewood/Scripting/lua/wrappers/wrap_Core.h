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
    
    public:
        static int w_getDeltaTime(lua_State* L);
        static int w_getDeltaTimeMiliseconds(lua_State* L);
        static int w_getTime(lua_State* L);
        static int w_getTimeMiliseconds(lua_State* L);

        wrap_Application(lua_State* L);
        virtual const char* GetName() const { return Name; }
    };

    class wrap_Window : public LuaWrapper
    {
    private:

        static const char* Name;
    public:
        static int w_setTitle(lua_State* L);
        static int w_getWidth(lua_State* L);
        static int w_getHeight(lua_State* L);

        wrap_Window(lua_State* L);
        virtual const char* GetName() const { return Name; }
    };
}