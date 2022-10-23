--lua class : SurviveGameMode
---@type MMOGameMode
local class = UnLua.Class()

function class:OverrideInitGame()
    require "World"
    CreateGlobalVar()
    --创建各种message
    local WorldContext = self:GetWorld()
    gWorld:InitializeWorld(WorldContext)
end
function class:ReceiveBeginPlay()
    print("ReceiveBeginPlay GameMode")
    if gWorld then
        gWorld:beginPlay()
    end
end

--[[
function class:ReceiveEndPlay()
end
--]]

function class:ReceiveTick(DeltaSeconds)
    if gWorld then
        gWorld:tick(DeltaSeconds)
        gWorld:lateTick(DeltaSeconds)
    end
end

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
