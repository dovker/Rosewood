SwordScript = {}

local Trans = nil;
local SpriteColor = nil;
local DefaultX = 0;
local Sprite = nil;
local Swing = false;
local FacingDir = -1;
local enT = nil;


local function ChangeFacing(facingDir)
    Trans.Position.x = DefaultX * facingDir;
    Trans.Rotation.z = -facingDir;
    FacingDir = -facingDir;
end
function SwordScript:OnCreate()
    Trans = self.Entity:GetTransfromComponent().Transform;
    Sprite = self.Entity:GetSpriteRenderComponent();
    SpriteColor = Sprite.Color;
    Sprite.Offset.Pivot = vec2:new(0.0, 0.5);
    DefaultX = Trans.Position.x;
end

function SwordScript:OnUpdate(ts)
    Trans = self.Entity:GetTransfromComponent().Transform;
    Sprite = self.Entity:GetSpriteRenderComponent();
    SpriteColor = Sprite.Color;

    if Swing then
        Trans.Rotation.z = vmath:lerp(Trans.Rotation.z, -FacingDir, 0.7);
        if (Trans.Rotation.z > 0.999 or Trans.Rotation.z < -0.99) then 
            Swing = false            
        end
    else
        Trans.Rotation.z = vmath:lerp(Trans.Rotation.z, FacingDir, 0.4);
    end
    SpriteColor.r = math.sin(Rosewood.Application:GetTime());
    SpriteColor.b = math.cos(Rosewood.Application:GetTime());
end

function SwordScript:OnKeyPressed(key)
    if(key == Keys.ENTER) then
        Swing = true;
    elseif(key == Keys.A) then
        InputLeft = 1;
        ChangeFacing(-1);
    elseif (key == Keys.D) then
        InputRight = 1;
        ChangeFacing(1);
    end
end

return SwordScript;