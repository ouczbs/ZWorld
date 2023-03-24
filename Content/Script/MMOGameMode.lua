--lua class : SurviveGameMode
---@type MMOGameMode
local class = UnLua.Class()

function class:ReceiveBeginPlay()
    if gWorld then
        gWorld:beginPlay()
    end
end

--[[
function class:ReceiveEndPlay()
end
--]]


--[[
function class:ReceiveAnyDamage(Damage, DamageType, InstigatedBy, DamageCauser)
end
--]]

--[[
function class:ReceiveActorBeginOverlap(OtherActor)
end
--]]

--[[
function class:ReceiveActorEndOverlap(OtherActor)
end
--]]

return class
