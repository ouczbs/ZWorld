--GameWorld.Blueprints.Character.BP_PlayerState_C
--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

require "UnLua"

local class = Class()

--function class:Initialize(Initializer)
--end

--function class:UserConstructionScript()
--end
function class:ReceiveBeginPlay()
    self:GetGameOwner()
end
function class:GetGameOwner()
    if not self.GameOwner then
        self.GameOwner = gWorld.UGameOwnerSubsystem:SpawnGameOwner()
    end
    return self.GameOwner
end
--function class:ReceiveEndPlay()
--end

-- function class:ReceiveTick(DeltaSeconds)
-- end

--function class:ReceiveAnyDamage(Damage, DamageType, InstigatedBy, DamageCauser)
--end

--function class:ReceiveActorBeginOverlap(OtherActor)
--end

--function class:ReceiveActorEndOverlap(OtherActor)
--end

return class
