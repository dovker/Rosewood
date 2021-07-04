#pragma once
#include "rwpch.h"
#include "LuaState.h"
#include "Rosewood/Files/File.h"
#include "Rosewood/Core/Timestep.h"


namespace Rosewood
{
    class Entity;

    class LuaScript
    {
    private:
        Ref<TextFile> m_Script;
        lua_State* L;
        bool m_Attached = false;
        std::string m_TableName;
    public:
        LuaScript() {}
        LuaScript(Ref<TextFile> file, const std::string& tableName = "");
        LuaScript(const std::string& fileName, const std::string& tableName = "");
        ~LuaScript();

        std::string GetTableName() { return m_TableName; }

        void AttachScript(lua_State* luaPtr);
        template <class T> void AttachValue(const std::string& name, T value);
        void CallScript();
        void CallVoidFunction(const std::string& fnName);

        void OnAttached(const Entity& entity);
		void OnDestroy();
		void OnUpdate(Timestep ts);
		void OnRender2D(); //TODO: GRAPHICS SCRIPTING

        void OnKeyPressed(int key);
        void OnKeyReleased(int key);
        void OnMouseButtonPressed(int key);
        void OnMouseButtonReleased(int key);
        void OnMouseMoved(float x, float y);
        void OnMouseScrolled(float xOffset, float yOffset);
    };
}