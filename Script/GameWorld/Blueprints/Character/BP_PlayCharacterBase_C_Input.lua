local class = GW.BP_PlayCharacterBase or {}
local Rotator = UE4.FRotator(0, 0, 0)
class["MoveForward/Backwards"] = function(self , Axis)
    if Axis == 0 then 
        return
    end
    Rotator.Yaw =  self:GetControlRotation().Yaw
    local Direction = UE4.UKismetMathLibrary.GetForwardVector(Rotator)
    self.MovementRequest:MakeRequest(Direction , Axis)
end

class["MoveRight/Left"] = function(self , Axis)
    if Axis == 0 then 
        return
    end
    Rotator.Yaw =  self:GetControlRotation().Yaw
    local Direction = UE4.UKismetMathLibrary.GetRightVector(Rotator)
    self.MovementRequest:MakeRequest(Direction , Axis)
end

class["LookUp/Down"] = function(self , Axis)
    if Axis == 0 then 
        return
    end
    local val = Axis * self["LookUp/DownRate"]
    self.ControllerLookRequest.Pitch = val
end

class["LookLeft/Right"] = function(self , Axis)
    if Axis == 0 then 
        return
    end
    local val = Axis * self.LookLeftRightRate
    self.ControllerLookRequest.Yaw = val
end

function class:JumpAction_Pressed()
    self:Jump()
end

function class:JumpAction_Released()
    self:StopJumping()
end

return class