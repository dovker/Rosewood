#include "rwpch.h"
#include "wrappers/wrapper.h"


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

        void CallVoidFunction(const char* fnName);// Fix later
        void CallVoidFunction(const char* fnName, const char* tableName);
        //Do Call and Get events

        //Automate the Wrrappers and Type stuff to pass in functions

        //Figure out how to return C reference from a function and be able to deal with it's values
    };
}