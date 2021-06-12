SampleScript = {}


function SampleScript:OnCreate()
    Rosewood.Window:SetTitle("Penis");
    Rosewood.Log:Critical("Ahahaha sheeeeesh");
    Rosewood.Log:Trace("AHAHA");
    Rosewood.Log:Info("AHAHA");
    Rosewood.Log:Warn("AHAHA");
    Rosewood.Log:Error("AHAHA");
end

function SampleScript:OnUpdate(ts)
    local b = Rosewood.Benchmark:new("Inside Lua Update");

    b:Stop();
end