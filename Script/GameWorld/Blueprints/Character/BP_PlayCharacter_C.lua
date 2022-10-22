--GameWorld.Blueprints.Character.BP_PlayCharacter_C
--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

require "UnLua"
local super = GW.BP_PlayCharacterBase or require("GameWorld.Blueprints.Character.BP_PlayCharacterBase_C")
local class = Class("BP_PlayCharacter" , super)

--function class:Initialize(Initializer)
--end

--function class:UserConstructionScript()
--end

function class:ReceiveBeginPlay()
    super.ReceiveBeginPlay(self)
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
