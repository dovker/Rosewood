#include "rwpch.h"
#include "wrappers/wrapper.h"

extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}
namespace Rosewood
{
    enum class LuaVar
    {
        NIL = 0,
        INT,
        FLOAT,
        BOOL,
        FUNCTION,
        STRING,
        USER_DATA,
        LIGHT_USER_DATA,
    };

    class LuaState
    {
    private:
        lua_State* L;
    public:
        LuaState(/* args */);
        ~LuaState();
        bool CheckError(int r);

        void ExecuteScript(const std::string& filepath);
        void CreateTable(const char* tableName);
        void CreateGlobalTable(const char* name);

        void CreateMetaTable(const char* name); 

        void CloseGlobal();
        void ClearStack();
        void PrintStack();
        void InsistGlobal(const char* name);

        void SetTableFunctions(const luaL_Reg* functions, int count);
        
        void PushTableNumber(const char* varName, float val);
        void PushTableFunction(const char* fnName, lua_CFunction fn);
        void PushTableInt(const char* varName, int val);
        void PushTableBool(const char* varName, bool val);




        void CallVoidFunction(const char* fnName);

        void CallFunction(const char* fnName, std::initializer_list<LuaVar>, ...);

        void InitType(const LuaWrapper& wrapper);
        //Do Call and Get events

        //Automate the Wrrappers and Type stuff to pass in functions

        //Figure out how to return C reference from a function and be able to deal with it's values
    };
}