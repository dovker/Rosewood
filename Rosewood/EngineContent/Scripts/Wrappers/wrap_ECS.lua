Rosewood.Scripts = {}

function Rosewood.Lua:CallVoidFn(name)
    for k, v in pairs(Rosewood.Scripts) do
        if v[name] ~= nil then v[name]() end
    end
end
function Rosewood.Lua:CallOnUpdate(ts)
    for k, v in pairs(Rosewood.Scripts) do
        if v["OnUpdate"] ~= nil then v["OnUpdate"](ts) end
    end
end

function Rosewood.Lua:AddScript(entity, name)
    Rosewood.Scripts[entity] = name:new(entity);
end

function Rosewood.Lua:RemoveScript(entity)
    Rosewood.Scripts[entity] = nil;
end