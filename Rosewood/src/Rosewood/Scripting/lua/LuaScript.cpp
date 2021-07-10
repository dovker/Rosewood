#include "rwpch.h"
#include "LuaScript.h"

#include "Rosewood/Files/FileSystem.h"
#include "Rosewood/Assets/AssetManager.h"
#include "Rosewood/ECS/Entity.h"


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
        std::pair<sol::protected_function, sol::table> GetFuntion(lua_State* L, const std::string& fnName, const std::string& tableName)
        {
            sol::state_view lua(L);
            sol::table t = lua[tableName];
            return std::make_pair(t[fnName], t);
        }
        void CheckResult(sol::protected_function_result result)
        {
            if (!result.valid()) {
                sol::error err = result;
                RW_LUA_ERROR("FAILED TO CALL FUNCTION: {0}", err.what());
            }
        }
    };

    LuaScript::LuaScript(Ref<TextFile> file, const std::string& tableName)
        : m_Script(file), m_TableName(tableName)
    {}
    LuaScript::LuaScript(const std::string& fileName, const std::string& tableName)
        : m_Script(AssetManager::Get<TextFile>(fileName)), m_TableName(tableName)
    {}
    LuaScript::~LuaScript()
    {

    }


    void LuaScript::AttachScript(Ref<LuaState> l)
    {
        L = l;
        m_Attached = true;
    }
    
    template<>
    void LuaScript::AttachValue(const std::string& name, int value)
    {
        sol::state_view lua(L->GetPointer());
        lua[m_TableName][name] = value;
    }
    template<>
    void LuaScript::AttachValue(const std::string& name, float value)
    {
        sol::state_view lua(L->GetPointer());
        lua[m_TableName][name] = value;
    }
    template<>
    void LuaScript::AttachValue(const std::string& name, const std::string& value)
    {
        sol::state_view lua(L->GetPointer());
        lua[m_TableName][name] = value;
    }
    template<>
    void LuaScript::AttachValue(const std::string& name, bool value)
    {
        sol::state_view lua(L->GetPointer());
        lua[m_TableName][name] = value;
    }
    template<>
    void LuaScript::AttachValue(const std::string& name, Entity value)
    {
        sol::state_view lua(L->GetPointer());
        lua[m_TableName][name] = value;
    }
    void LuaScript::CallScript()
    {
        sol::state_view lua(L->GetPointer());
        
        lua.safe_script(m_Script->GetData(), [](lua_State*, sol::protected_function_result pfr)
        {
            sol::error err = pfr;
            RW_LUA_ERROR("Error occured calling script: {0}", err.what());
            return pfr;
        });
    }

    void LuaScript::CallVoidFunction(const std::string& fnName)
    {
        auto [fn, t] = Helper::GetFuntion(L->GetPointer(), fnName, m_TableName);
        if(!fn.valid()) return;
        Helper::CheckResult(fn(t));
    }

    void LuaScript::OnAttached()
    {
        CallVoidFunction("OnCreate");
    }
    void LuaScript::OnDestroy()
    {
        CallVoidFunction("OnDestroy");
    }
    void LuaScript::OnUpdate(Timestep ts)
    {
        auto [fn, t] = Helper::GetFuntion(L->GetPointer(), "OnUpdate", m_TableName);
        if(!fn.valid()) return;
        Helper::CheckResult(fn(t, ts.GetSeconds()));
    }
    void LuaScript::OnRender2D()
    {
        CallVoidFunction("OnRender2D");
    }
    void LuaScript::OnKeyPressed(int key)
    {
        auto [fn, t] = Helper::GetFuntion(L->GetPointer(), "OnKeyPressed", m_TableName);
        if(!fn.valid()) return;
        Helper::CheckResult(fn(t, key));
    }
    void LuaScript::OnKeyReleased(int key)
    {
        auto [fn, t] = Helper::GetFuntion(L->GetPointer(), "OnKeyReleased", m_TableName);
        if(!fn.valid()) return;
        Helper::CheckResult(fn(t, key));
    }
    void LuaScript::OnMouseButtonPressed(int key)
    {
        auto [fn, t] = Helper::GetFuntion(L->GetPointer(), "OnMouseButtonPressed", m_TableName);
        if(!fn.valid()) return;
        Helper::CheckResult(fn(t, key));
    }
    void LuaScript::OnMouseButtonReleased(int key)
    {
        auto [fn, t] = Helper::GetFuntion(L->GetPointer(), "OnMouseButtonReleased", m_TableName);
        if(!fn.valid()) return;
        Helper::CheckResult(fn(t, key));
    }
    void LuaScript::OnMouseMoved(float x, float y)
    {
        auto [fn, t] = Helper::GetFuntion(L->GetPointer(), "OnMouseMoved", m_TableName);
        if(!fn.valid()) return;
        Helper::CheckResult(fn(t, x, y));
    }
    void LuaScript::OnMouseScrolled(float xOffset, float yOffset)
    {
        auto [fn, t] = Helper::GetFuntion(L->GetPointer(), "OnMouseScrolled", m_TableName);
        if(!fn.valid()) return;
        Helper::CheckResult(fn(t, xOffset, yOffset));
    }

}
