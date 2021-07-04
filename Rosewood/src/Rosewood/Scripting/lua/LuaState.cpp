#include "rwpch.h"
#include "LuaState.h"
#include "wrappers/wrap_Debug.h"
#include "wrappers/wrap_Core.h"
#include "wrappers/wrap_Input.h"
#include "wrappers/wrap_Math.h"
#include "wrappers/wrap_ECS.h"


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

        wrap_ECS ecs(L);
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
        if (FileSystem::Exists(std::filesystem::path(filepath)))
        {
            int result = luaL_dofile(L, filepath.c_str());
            RW_CORE_ASSERT(CheckError(result), "Lua File Error!!");//Fix this for engine use
        }
        else
        {
            RW_CORE_ERROR("FILE: {0} Does not exist.", filepath);
        }
    }
    void LuaState::ExecuteScript(const Ref<TextFile>& file)
    {
        RW_CORE_ASSERT(CheckError(luaL_dostring(L, file->GetData().c_str())), "LuaScript Error!!");//Fix this for engine use
    }
    void LuaState::CallVoidFunction(const char* fnName)
    {
        lua_getfield(L, -1, fnName);
        if(lua_isfunction(L, -1))
        {
            CheckError(lua_pcall(L, 0, 0, 0));
        }
    }
}