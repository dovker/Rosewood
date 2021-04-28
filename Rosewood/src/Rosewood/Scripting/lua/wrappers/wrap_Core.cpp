#include "rwpch.h"

#include "Rosewood/Core/Application.h"
#include "Rosewood/Core/Window.h"

#include "wrap_Core.h"

namespace Rosewood
{
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