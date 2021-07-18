Rosewood.Scripts = {}
Rosewood.Lua = {}

function Rosewood.Lua.CallVoidFn(name)
    for k, v in pairs(Rosewood.Scripts) do
        if v ~= nil and v[name] ~= nil then v[name](v) end
    end
end
function Rosewood.Lua.CallVoidIndividualFn(entity, fnName)
    local scr = Rosewood.Scripts[entity:GetID()]
    if scr ~= nil and scr[fnName] ~= nil then
        scr[fnName](scr)
    end
end
function Rosewood.Lua.CallOnUpdate(ts)
    for k, v in pairs(Rosewood.Scripts) do
        if v.OnUpdate ~= nil then v:OnUpdate(ts) end
    end
end
function Rosewood.Lua.CallOnKeyPressed(key)
    for k, v in pairs(Rosewood.Scripts) do
        if v.OnKeyPressed ~= nil then v:OnKeyPressed(key) end
    end
end
function Rosewood.Lua.CallOnKeyReleased(key)
    for k, v in pairs(Rosewood.Scripts) do
        if v.OnKeyReleased ~= nil then v:OnKeyReleased(key) end
    end
end
function Rosewood.Lua.CallOnMouseButtonPressed(key)
    for k, v in pairs(Rosewood.Scripts) do
        if v.OnMouseButtonPressed ~= nil then v:OnMouseButtonPressed(key) end
    end
end
function Rosewood.Lua.CallOnMouseButtonReleased(key)
    for k, v in pairs(Rosewood.Scripts) do
        if v.OnMouseButtonReleased ~= nil then v:OnMouseButtonReleased(key) end
    end
end
function Rosewood.Lua.CallOnMouseMoved(x, y)
    for k, v in pairs(Rosewood.Scripts) do
        if v.OnMouseMoved ~= nil then v:OnMouseMoved(x, y) end
    end
end
function Rosewood.Lua.CallOnMouseScrolled(xOffset, yOffset)
    for k, v in pairs(Rosewood.Scripts) do
        if v.OnMouseScrolled ~= nil then v:OnMouseScrolled(xOffset, yOffset) end
    end
end
function Rosewood.Lua.DestroyScripts()
    for k, v in pairs(Rosewood.Scripts) do
        if v.OnDetached ~= nil then v:OnDetached() end
        Rosewood.Scripts[k] = nil;
    end
end

function Rosewood.Lua.AddScript(entity, name)
    name.Entity = -1;
    name.__index = name;
    Rosewood.Scripts[entity:GetID()] = setmetatable({Entity = entity}, name);
end



function Rosewood.Lua.RemoveScript(entity)
    local scr = Rosewood.Scripts[entity:GetID()]
    if scr ~= nil then
        if scr["OnDelete"]() ~= nil then scr["OnDelete"](scr) end
        Rosewood.Scripts[entity:GetID()] = nil;
    end
end