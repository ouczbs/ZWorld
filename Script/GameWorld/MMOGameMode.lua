--lua class : MMOGameMode
require "UnLua"
print("lua class : MMOGameMode")
local class = Class("MMOGameMode")

function class:OnInitGame()
    require "GamePlay.World"
    require "GamePlay.GameGlobal"
    --创建各种message
    gWorld:InitializeLuaWorld()
    gWorld:InitializeGameWorld(self)
    print("OnInitGame")
end
function class:ReceiveBeginPlay()
    gWorld:beginPlay()
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
