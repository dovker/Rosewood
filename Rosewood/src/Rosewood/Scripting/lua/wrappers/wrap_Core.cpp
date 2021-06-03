#include "rwpch.h"

#include "Rosewood/Core/Application.h"
#include "Rosewood/Core/Window.h"

#include "wrap_Core.h"

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

namespace Rosewood
{
    const char* wrap_Application::Name = "Application";

    luaL_Reg* wrap_Application::w_functions = 
        (luaL_Reg[]){
            {"GetDeltaTime",            wrap_Application::w_getDeltaTime},
            {"GetDeltaTimeMiliseconds", wrap_Application::w_getDeltaTimeMiliseconds},
            {"GetTime",                 wrap_Application::w_getTime},
            {"GetTimeMiliseconds",      wrap_Application::w_getTimeMiliseconds},

        };

    int wrap_Application::functionCount = 4; 

    int wrap_Application::w_getDeltaTime(lua_State* L)
    {
        lua_pushnumber(L, Rosewood::Application::GetDeltaTime());
        return 1;
    }

    int wrap_Application::w_getDeltaTimeMiliseconds(lua_State* L)
    {
        lua_pushnumber(L, Rosewood::Application::GetDeltaTime() * 1000.0f);
        return 1;
    }

    int wrap_Application::w_getTime(lua_State* L)
    {
        lua_pushnumber(L, Rosewood::Application::GetTime());
        return 1;
    }

    int wrap_Application::w_getTimeMiliseconds(lua_State* L)
    {
        lua_pushnumber(L, Rosewood::Application::GetTime() * 1000.0f);
        return 1;
    }

    const char* wrap_Window::Name = "Window";

    luaL_Reg* wrap_Window::w_functions = 
        (luaL_Reg[]){
            {"SetTitle",    wrap_Window::w_setTitle},
            {"GetWidth",    wrap_Window::w_getWidth},
            {"GetHeight",   wrap_Window::w_getHeight}
        };
    
    int wrap_Window::functionCount = 3;

    int wrap_Window::w_setTitle(lua_State* L)
    {
        Application::Get().GetWindow().SetTitle(lua_tostring(L, -1));
        return 0;
    }

    int wrap_Window::w_getWidth(lua_State* L)
    {
        lua_pushinteger(L, Application::Get().GetWindow().GetWidth());
        return 1;
    }
    
    int wrap_Window::w_getHeight(lua_State* L)
    {
        lua_pushinteger(L, Application::Get().GetWindow().GetHeight());
        return 1;
    }
}