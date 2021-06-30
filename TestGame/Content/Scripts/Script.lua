SampleScript = {}

local Trans = nil;
local Speed = 2;
local InputLeft = 0;
local InputRight = 0;
local InputUp = 0;
local InputDown = 0;

function SampleScript:OnCreate(entity)
    Trans = entity:TransfromComponent().Transform;
end

function SampleScript:OnUpdate(ts)
    local dir = vec3:new(InputRight - InputLeft, InputDown - InputUp, 0.0);
    if(dir.x ~= 0.0 and dir.y ~= 0.0) then
        dir = dir:normalize();
    end
    Trans.Position:add(dir * Speed);
end


function SampleScript:OnKeyPressed(key)
    if(key == Keys.A) then
        InputLeft = 1;
    elseif (key == Keys.D) then
        InputRight = 1;
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

-- function SampleScript:OnMessageReceived(entity, messageData)
-- end