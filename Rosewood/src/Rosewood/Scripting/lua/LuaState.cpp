#include "rwpch.h"
#include "LuaState.h"
#include "wrappers/wrap_Debug.h"
#include "wrappers/wrap_Core.h"
#include "wrappers/wrap_Input.h"
#include "wrappers/wrap_Math.h"
#include "wrappers/wrap_ECS.h"
#include "Rosewood/ECS/Entity.h"


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
    namespace Helper
    {
        void CheckResult(sol::protected_function_result result)
        {
            if (!result.valid()) {
                sol::error err = result;
                RW_LUA_ERROR("FAILED TO CALL FUNCTION: {0}", err.what());
            }
        }
    };

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
        ExecuteScript(FileSystem::GetPath("Scripts/Wrappers/wrap_ECS.lua", FilePathType::ENGINE));
        ExecuteScript(FileSystem::GetPath("Scripts/Defines.lua", FilePathType::ENGINE));
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
            int result = luaL_dofile(L, filepath.c_str());
            RW_CORE_ASSERT(CheckError(result), "Lua File Error!!");//Fix this for engine use
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
    void LuaState::CallScript(Ref<TextFile> script)
    {
        sol::state_view lua(L);
        
        lua.safe_script(script->GetData(), [](lua_State*, sol::protected_function_result pfr)
        {
            sol::error err = pfr;
            RW_LUA_ERROR("Error occured calling script: {0}", err.what());
            return pfr;
        });
    }
    void LuaState::RegisterScript(const Entity& entity, const std::string& tableName)
    {
        sol::state_view lua(L);
        Helper::CheckResult(lua["Rosewood"]["Lua"]["AddScript"](entity, lua[tableName]));
    }
    void LuaState::UnregisterScript(const Entity& entity)
    {
        sol::state_view lua(L);
        Helper::CheckResult(lua["Rosewood"]["Lua"]["RemoveScript"](entity));
    }
    void LuaState::DestroyScripts()
    {
        sol::state_view lua(L);
        Helper::CheckResult(lua["Rosewood"]["Lua"]["DestroyScripts"]());
    }

    void LuaState::CallVoidScriptFunction(const std::string& fnName)
    {
        sol::state_view lua(L);
        Helper::CheckResult(lua["Rosewood"]["Lua"]["CallVoidFn"](fnName));
    }
    void LuaState::CallVoidIndividualFunction(const Entity& entity, const std::string& fnName)
    {
        sol::state_view lua(L);
        Helper::CheckResult(lua["Rosewood"]["Lua"]["CallVoidIndividualFn"](entity, fnName));
    }
    void LuaState::CallOnUpdate(float ts)
    {
        sol::state_view lua(L);
        Helper::CheckResult(lua["Rosewood"]["Lua"]["CallOnUpdate"](ts));
    }
    void LuaState::CallOnKeyPressed(int key)
    {
        sol::state_view lua(L);
        Helper::CheckResult(lua["Rosewood"]["Lua"]["CallOnKeyPressed"](key));
    }
    void LuaState::CallOnKeyReleased(int key)
    {
        sol::state_view lua(L);
        Helper::CheckResult(lua["Rosewood"]["Lua"]["CallOnKeyReleased"](key));
    }
    void LuaState::CallOnMouseButtonPressed(int key)
    {
        sol::state_view lua(L);
        Helper::CheckResult(lua["Rosewood"]["Lua"]["CallOnMouseButtonPressed"](key));
    }
    void LuaState::CallOnMouseButtonReleased(int key)
    {
        sol::state_view lua(L);
        Helper::CheckResult(lua["Rosewood"]["Lua"]["CallOnMouseButtonReleased"](key));
    }
    void LuaState::CallOnMouseMoved(float x, float y)
    {
        sol::state_view lua(L);
        Helper::CheckResult(lua["Rosewood"]["Lua"]["CallOnMouseMoved"](x, y));
    }
    void LuaState::CallOnMouseScrolled(float xOffset, float yOffset)
    {
        sol::state_view lua(L);
        Helper::CheckResult(lua["Rosewood"]["Lua"]["CallOnMouseScrolled"](xOffset, yOffset));
    }
}
