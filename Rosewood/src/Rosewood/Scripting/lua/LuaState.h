#pragma once

#include "rwpch.h"
#include "wrappers/wrapper.h"
#include "Rosewood/Files/File.h"


namespace Rosewood
{
    class Entity;

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

        void CallScript(Ref<TextFile> script);
        void RegisterScript(const Entity& entity, const std::string& tableName);
        void UnregisterScript(const Entity& entity);
        void DestroyScripts();

        static Ref<LuaState> Create()
        {
            return CreateRef<LuaState>();
        }

        void CallVoidScriptFunction(const std::string& fnName);
        void CallVoidIndividualFunction(const Entity& entity, const std::string& fnName);
        void CallOnUpdate(float ts);
        void CallOnKeyPressed(int key);
        void CallOnKeyReleased(int key);
        void CallOnMouseButtonPressed(int key);
        void CallOnMouseButtonReleased(int key);
        void CallOnMouseMoved(float x, float y);
        void CallOnMouseScrolled(float xOffset, float yOffset);
    };
}