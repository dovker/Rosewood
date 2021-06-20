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
#include "sol/sol.hpp"


namespace Rosewood
{
    const char* wrap_Application::Name = "Application";
    wrap_Application::wrap_Application(lua_State * L)
    {
        sol::state_view lua(L);

        auto ns = lua["Rosewood"].get_or_create<sol::table>();

        auto table = lua.create_table_with(
            "GetDeltaTime",            Application::GetDeltaTime,
            "GetTime",                 Application::GetTime
        );
        ns["Application"] = table;
    }


    const char* wrap_Window::Name = "Window";

    wrap_Window::wrap_Window(lua_State * L)
    {
        sol::state_view lua(L);

        auto ns = lua["Rosewood"].get_or_create<sol::table>();

        auto table = lua.create_table_with(
            "SetTitle",            wrap_Window::w_setTitle,
            "GetWidth",            wrap_Window::w_getWidth,
            "GetHeight",           wrap_Window::w_getHeight   
        );
        ns["Window"] = table;
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