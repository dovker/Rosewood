SampleScript = {}


function SampleScript:OnCreate()
    Rosewood.Log:Critical("Ahahaha sheeeeesh");
    Rosewood.Log:Trace("AHAHA");
    Rosewood.Log:Info("AHAHA");
    Rosewood.Log:Warn("AHAHA");
    Rosewood.Log:Error("AHAHA");
    Rosewood.Log:LuaCritical("Ahahaha sheeeeesh");
    Rosewood.Log:LuaTrace("AHAHA");
    Rosewood.Log:LuaInfo("AHAHA");
    Rosewood.Log:LuaWarn("AHAHA");
    Rosewood.Log:LuaError("AHAHA");
end

function SampleScript:OnUpdate(ts)
    local b = Rosewood.Benchmark:new("Inside Lua Update");

    b:Stop();
end