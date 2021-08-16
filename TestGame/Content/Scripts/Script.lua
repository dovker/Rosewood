SampleScript = {}

local Trans = nil;
local Speed = 2;
local InputLeft = 0;
local InputRight = 0;
local InputUp = 0;
local InputDown = 0;
local SwordTrans = nil;

local function ChangeFacing(facingDir)
    Trans.Rotation.y = math.pi * facingDir;
end

function SampleScript:OnCreate()
    --Maybe try Scene:GetEntity(self.entity);
    self.Entity:GetSpriteRenderComponent().Offset.Pivot.x = 0.5;
end

function SampleScript:OnUpdate(ts)
    Trans = self.Entity:GetTransfromComponent().Transform;
    local dir = vec3:new(InputRight - InputLeft, InputDown - InputUp, 0.0);
    if(dir.x ~= 0.0 or dir.y ~= 0.0) then
        dir = dir:normalize();
    end
    -- --Trans.Position:add(vec3:new(0.8, 0.0, 0.0));
    Trans.Position:add(dir * Speed * ts * 60.0);
    Rosewood.Log:Trace("PENIS")
    Rosewood.Log:Info("PENIS")
    Rosewood.Log:Error("PENIS")
    Rosewood.Log:Critical("PENIS")
    Rosewood.Log:Warn("PENIS")
end


function SampleScript:OnKeyPressed(key)
    if(key == Keys.A) then
        InputLeft = 1;
        ChangeFacing(1);
    elseif (key == Keys.D) then
        InputRight = 1;
        ChangeFacing(0);
    elseif (key == Keys.S) then
        InputDown = 1;
    elseif (key == Keys.W) then
        InputUp = 1;
    end
end

function SampleScript:OnKeyReleased(key)
    if(key == Keys.A) then
        InputLeft = 0;
    elseif (key == Keys.D) then
        InputRight = 0;
    elseif (key == Keys.S) then
        InputDown = 0;
    elseif (key == Keys.W) then
        InputUp = 0;
    end
end

return SampleScript;
-- function SampleScript:OnMessageReceived(entity, messageData)
-- end