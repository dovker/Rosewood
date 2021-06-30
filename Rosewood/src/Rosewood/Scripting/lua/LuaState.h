#pragma once


#include "rwpch.h"
#include "wrappers/wrapper.h"
#include "Rosewood/Files/File.h"


namespace Rosewood
{
    class LuaState
    {
    private:
        lua_State* L;
    public:
        LuaState(/* args */);
        ~LuaState();
        bool CheckError(int r);

        void ExecuteScript(const std::string& filepath);
        void ExecuteScript(const Ref<TextFile>& file);

        lua_State* GetPointer() { return L; }

        void CallVoidFunction(const char* fnName);// Fix later
        void CallVoidFunction(const char* fnName, const char* tableName);

        static Ref<LuaState> Create()
        {
            return CreateRef<LuaState>();
        }
    };
}