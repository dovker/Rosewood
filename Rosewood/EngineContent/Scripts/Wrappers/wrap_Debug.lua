local function ConnectSentence(message)
    return os.date("[%H:%M:%S]") .. " LUA: " .. message
end

function Rosewood.Log:LuaTrace(message)
    print("\27[37m" .. ConnectSentence(message) .. "\27[0m")
end

function Rosewood.Log:LuaInfo(message)
    print("\27[32m" .. ConnectSentence(message) .. "\27[0m")
end

function Rosewood.Log:LuaWarn(message)
    print("\27[1;33m" .. ConnectSentence(message) .. "\27[0m")
end
function Rosewood.Log:LuaError(message)
    print("\27[1;31m" .. ConnectSentence(message) .. "\27[0m")
end
function Rosewood.Log:LuaCritical(message)
    print("\27[1;41m" .. ConnectSentence(message) .. "\27[0m")
end