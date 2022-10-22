--GameWorld.Blueprints.Character.BP_PlayCharacterBase_C
--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

require "UnLua"
print("Require BP_PlayCharacterBase_C")
local class = Class("BP_PlayCharacterBase")
require("GameWorld.Blueprints.Character.BP_PlayCharacterBase_C_Input")
--function class:Initialize(Initializer)
--end

--function class:UserConstructionScript()
--end
function class:TickControllerLook(dt)
    
end
function class:InitRequests(GameOwner)
    local MovementRequest = GameOwner:FindOrAddRequest(GA.Request.Movement)
    MovementRequest:PushRequest()
    MovementRequest.Pawn = self
    self.MovementRequest = MovementRequest

    local ControllerLookRequest = GameOwner:FindOrAddRequest(GA.Request.ControllerLook)
    ControllerLookRequest:PushRequest()
    ControllerLookRequest.Pawn = self
    self.ControllerLookRequest = ControllerLookRequest

    local MantleRequest = GameOwner:FindOrAddRequest(GA.Request.ControllerLook)
end

function class:ReceiveBeginPlay()
    local PlayerState = self:GetController().PlayerState
    if PlayerState then
        self.GameOwner =  PlayerState:GetGameOwner()
        self:InitRequests(self.GameOwner)
    end
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
