SampleScript = {}


function SampleScript:OnCreate()
    Rosewood.Window:SetTitle("Balls");
    Rosewood.Log:Critical("Ahahaha");
    Rosewood.Log:Trace("AHAHA");
    Rosewood.Log:Info("AHAHA");
    Rosewood.Log:Warn("AHAHA");
    Rosewood.Log:Error("AHAHA");
    -- local v = glm.vec3:new(1.0, 1.0, 1.0);
    -- v:add(1.0);
    -- v:mul(0.4);
    -- v:mul(4.0, 1.0, 2.0);
    -- v:div(glm.vec3:new(5.0))

    local v2 = vec2:new(1.0, 1.0)

    v2 = v2:mul(0.4)
    v2 = v2:mul(vec2:new(4.0, 2.0))

    v2 = v2:div(vec2:new(5.0))

    v2 = v2 * 5.0

    print(vmath:clamp(1.1, 0.0, 1.0))

    v2 = vmath:clamp(v2, vec2:new(0.0, 0.0), vec2:new(1.0, 1.0))

    print(v2)

    local tr = Transform:new()
    tr.Position = tr.Position:mul(39)
    tr.Position = tr.Position:add(vec3:new(40))
    print(tr.Position)
    print(tr.Rotation)
    print(tr.Scale)

    local rectangle = Rect:new(0, 0, 100, 100)
    rectangle.Size = vec2:new(10, 10)

    print(rectangle.Size)

end

function SampleScript:OnUpdate()
    local b = Rosewood.BenchmarkTimer:new("Inside Lua Update");
    if(Rosewood.Input:IsKeyPressed(Keys.A)) then
        print("PRESSED");
    end

    b:Stop();
end