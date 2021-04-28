#include "LuaState.h"
#include "wrappers/wrap_Debug.h"
#include "wrappers/wrap_Core.h"


namespace Rosewood
{

    LuaState::LuaState(/* args */)
    {
        L = luaL_newstate();
        luaL_openlibs(L);

        wrap_Log log;
        InitType(log);
        ExecuteScript("EngineContent/Scripts/Wrappers/wrap_Debug.lua");

        wrap_Benchmark benchmark;
        InitType(benchmark);

        wrap_Window window;
        InitType(window);  

        wrap_Application app;
        InitType(app);  
    }

    LuaState::~LuaState()
    {
        lua_close(L);
    }
    void LuaState::InsistGlobal(const char* name)
    {
        lua_getglobal(L, name);

        if (!lua_istable(L, -1))
        {
            lua_pop(L, 1); // Pop the non-table.
            lua_newtable(L);
            lua_pushvalue(L, -1);
            lua_setglobal(L, name);
        }
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
    void LuaState::PrintStack()
    {
        for (int i = 1; i <= lua_gettop(L); i++)
            RW_LUA_TRACE("{0} - {1}", i, luaL_typename(L, i));
    }
    void LuaState::ExecuteScript(const std::string& filepath)
    {
        std::filesystem::path fp = filepath;
        RW_CORE_ASSERT(CheckError(luaL_dofile(L, fp.c_str())), "Lua File Not Found!!");//Fix this for engine use
    }
    void LuaState::CreateGlobalTable(const char* name)
    {
        lua_newtable(L);
        int TableIdx = lua_gettop(L);
        lua_pushvalue(L, TableIdx);
        lua_setglobal(L, name);
    }
    void LuaState::CreateTable(const char* name)
    {
        lua_newtable(L);
        int TableIdx = lua_gettop(L);
        lua_pushvalue(L, TableIdx);
        lua_setfield(L, 1, name);
    }
    void LuaState::CloseGlobal()
    {
        lua_remove(L, -3); // love
        //lua_gettop(L); //FIX THIS 
    }
    void LuaState::SetTableFunctions(const luaL_Reg* functions, int count)
    {
        if (functions == nullptr)
            return;

        for (int i = 0; i < count; i++)
        {
            lua_pushcfunction(L, (functions + i)->func);
            lua_setfield(L, -2, (functions + i)->name);
        }
    }
    void LuaState::PushTableFunction(const char* fnName, lua_CFunction fn)
    {
        lua_pushcfunction(L, fn);
        lua_setfield(L, -2, fnName);
    }
    void LuaState::PushTableBool(const char* varName, bool val)
    {
        lua_pushboolean(L, val ? 1 : 0);
        lua_setfield(L, -2, varName);
    }
    void LuaState::PushTableNumber(const char* varName, float val)
    {
        lua_pushnumber(L, (lua_Number)val);
        lua_setfield(L, -2, varName);
    }
    void LuaState::PushTableInt(const char* varName, int val)
    {
        lua_pushinteger(L, val);
        lua_setfield(L, -2, varName);
    }
    void LuaState::CallVoidFunction(const char* fnName)
    {
        lua_getfield(L, -1, fnName);
        if(lua_isfunction(L, -1))
        {
            CheckError(lua_pcall(L, 0, 0, 0));
        }
    }
    void LuaState::CreateMetaTable(const char* name)
    {
        luaL_newmetatable(L, name);
        lua_pushvalue(L, -1);
    }
    //Call_Function<void>("Name", arg, arg, arg);

    void LuaState::CallFunction(const char* fnName, std::initializer_list<LuaVar> vars, ...) //TODO: FIX THIS FUCKER
    {
        // lua_getfield(L, -1, fnName);
        // //lua_getglobal(L, fnName);
        // if(lua_isfunction(L, -1))
        // {
        //     va_list args;
        //     va_start(args, vars);
        //     for(auto v : vars)
        //     {
        //         switch (v)
        //         {
        //         case LuaVar::INT:
        //             lua_pushinteger(L, va_arg(args, int));
        //             break;
        //         case LuaVar::FLOAT:
        //             lua_pushnumber(L, va_arg(args, float));
        //             break;
        //         case LuaVar::BOOL:
        //             lua_pushboolean(L, va_arg(args, bool));
        //             break;
        //         case LuaVar::LIGHT_USER_DATA:
        //             lua_pushlightuserdata(L, va_arg(args, void*));
        //             break;
        //         case LuaVar::STRING:
        //             lua_pushstring(L, va_arg(args, const char*));
        //             break;
        //         default:
        //             lua_pushnil(L);
        //             break;
        //         }
        //         CheckError(lua_pcall(L, vars.size(), 0, 0));
        //     }
        //     va_end(args);
        // }
        // else{
        //     std::cout<<"FUNCTION NOT FOUND"<<std::endl;
        // }
    }
    void LuaState::ClearStack()
    {
        lua_settop(L, 0);
    }
    void LuaState::InitType(const LuaWrapper& wrapper)
    {
        if(wrapper.GetMetaFunctionCount() > 0)
        {
            CreateMetaTable(wrapper.GetMetaName());
            SetTableFunctions(wrapper.GetMetafunctions(), wrapper.GetMetaFunctionCount());
            RW_CORE_ASSERT(lua_istable(L, -1), "NOT METATABEL");

            ClearStack();
        }

        InsistGlobal("Rosewood");

        CreateTable(wrapper.GetName());
        RW_LUA_INFO(wrapper.GetName());

        RW_CORE_ASSERT(lua_istable(L, -1), "NOT TABEL");

        if(wrapper.GetFunctionCount() > 0)
        {
            SetTableFunctions(wrapper.GetFunctions(), wrapper.GetFunctionCount());
        }
        //CloseGlobal();

        ClearStack(); // RETRY LATER, Not sure if efficient

    }
}