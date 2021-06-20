#include "LuaState.h"
#include "wrappers/wrap_Debug.h"
#include "wrappers/wrap_Core.h"
#include "wrappers/wrap_Input.h"
#include "wrappers/wrap_Math.h"



#include "Rosewood/Files/FileSystem.h"

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}
#include "sol/sol.hpp"


namespace Rosewood
{

    LuaState::LuaState(/* args */)
    {
        L = luaL_newstate();
        luaL_openlibs(L);
        
        wrap_Log log(L);
        ExecuteScript(FileSystem::GetPath("Scripts/Wrappers/wrap_Debug.lua", FilePathType::ENGINE));

        wrap_Benchmark benchmark(L);

        wrap_Window window(L);

        wrap_Application app(L);
        wrap_Input input(L);

        wrap_Math math(L);
    }

    LuaState::~LuaState()
    {
        lua_close(L);
    }

    bool LuaState::CheckError(int r)
    {
        if(r != LUA_OK)
        {
            std::string errormsg = lua_tostring(L, -1);
            RW_LUA_ERROR(errormsg);
        }
        return true;
    }

    void LuaState::ExecuteScript(const std::string& filepath)
    {
        std::filesystem::path fp = filepath;
        RW_CORE_ASSERT(CheckError(luaL_dofile(L, fp.c_str())), "Lua File Not Found!!");//Fix this for engine use
    }
    void LuaState::CallVoidFunction(const char* fnName)
    {
        lua_getfield(L, -1, fnName);
        if(lua_isfunction(L, -1))
        {
            CheckError(lua_pcall(L, 0, 0, 0));
        }
    }
    void LuaState::CallVoidFunction(const char* fnName, const char* tableName)
    {
        sol::state_view lua(L);
        sol::protected_function fn = lua[tableName][fnName];//CATCH ERRORS
        sol::protected_function_result result = fn();
        if (!result.valid()) {
            // Call failed
            sol::error err = result;
            std::string what = err.what();
            RW_LUA_ERROR("FAILED TO CALL FUNCTION: {0}", what);
            // 'what' Should read
            // "Handled this message: negative number detected"
        }
    }
}