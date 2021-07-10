CameraScript = {}

local ZoomSpeed = 0.3;
local InputUp = 0;
local InputDown = 0;
local Trans = nil;

function CameraScript:OnCreate()
    Trans = self.Entity:GetTransfromComponent().Transform;
    Trans.Scale = vec3:new(2.0);
end

function CameraScript:OnUpdate(ts)
    Trans = self.Entity:GetTransfromComponent().Transform;
    local zoomVal = (InputDown - InputUp) * ZoomSpeed;
    Trans.Scale:add(vec3:new(zoomVal, zoomVal, 0.0));
    local clampedZoom = vmath:clamp(Trans.Scale.x, 0.1, 1.0);
    Trans.Scale = vec3:new(clampedZoom, clampedZoom, 1.0);
end


function CameraScript:OnKeyPressed(key)
    if (key == Keys.DOWN) then
        InputDown = 1;
    elseif (key == Keys.UP) then
        InputUp = 1;
    end
end

function CameraScript:OnKeyReleased(key)
    if (key == Keys.DOWN) then
        InputDown = 0;
    elseif (key == Keys.UP) then
        InputUp = 0;
    end
end