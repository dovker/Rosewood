SwordScript = {}

local Trans = nil;
local SpriteColor = nil;
local Sprite = nil

function SwordScript:OnCreate(entity)
    Trans = entity:TransfromComponent().Transform;
    Sprite = entity:SpriteRenderComponent()
    SpriteColor = Sprite.Color;
    Sprite.Offset.Pivot = vec2:new(0.0, 0.5);
end

function SwordScript:OnUpdate(ts)
    Trans.Rotation.z = math.sin(Rosewood.Application:GetTime());
    SpriteColor.r = math.sin(Rosewood.Application:GetTime());
    SpriteColor.b = math.cos(Rosewood.Application:GetTime());
end