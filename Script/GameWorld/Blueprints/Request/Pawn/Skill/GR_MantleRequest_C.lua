--GameWorld.Blueprints.Request.Pawn.Skill.GR_MantleRequest_C
require "UnLua"

local class = Class()

function class:GetCapsuleLocationfromBase(BaseLocation , ZOffset)
    local Capsule = self.Pawn.CapsuleComponent
    local height = Capsule:GetScaledCapsuleHalfHeight() + ZOffset
    return BaseLocation + UE4.FVector( 0  , 0 , height )
end
function class:GetCalpsuleBaseLocation(ZOffset)
    local capsuleComponent = self.Pawn.CapsuleComponent
    local location = capsuleComponent:K2_GetComponentLocation()
    local up = capsuleComponent:GetUpVector()
    local height = capsuleComponent:GetScaledCapsuleHalfHeight()
    return location - up * (height + ZOffset)
end
function class:GetPlayerMovementInput()
    local Pawn = self.Pawn
    local moveForward = Pawn:GetInputAxisValue("MoveForward/Backwards")
    local moveRight = Pawn:GetInputAxisValue("MoveRight/Left")
    local rotation = Pawn:GetControlRotation()
    local vector = UE4.FVector(0 , 0 , rotation.Yaw)
    local result = vector * moveForward + vector * moveRight
    return UE4.UKismetMathLibrary.Normal(result , 0.0001)
end
function class:MantleCheck(TraceSettings , DebugType)
    local WorldContext = gWorld:getWorldContext()
    local baseLocation = self:GetCalpsuleBaseLocation(2.0)
    local moveInput = self:GetPlayerMovementInput()
    local height = (TraceSettings.MaxLedgeHeight + TraceSettings.MinLedgeHeight) / 2
    local halfHeight = (TraceSettings.MaxLedgeHeight - TraceSettings.MinLedgeHeight) / 2 + 1
    local startVector = baseLocation + moveInput * -30 + UE4.FVector(0 , 0 , height)
    local endVector = startVector + moveInput * TraceSettings.ReachDistance
    local OutHit = nil
    UE4.UKismetSystemLibrary.CapsuleTraceSingle( WorldContext, startVector , endVector,
    TraceSettings.ForwardTraceRadius , halfHeight , UE4.ETraceTypeQuery.Climbable, false , nil ,DebugType , OutHit , true)
    local bWalkAble = self.Pawn.CharacterMovement:IsWalkable(OutHit)
    if bWalkAble or not OutHit.bBlockingHit or OutHit.bStartPenetrating then 
        return false
    end

    local InitialTrace_ImpactPoint = OutHit.ImpactPoint
    local InitialTrace_Normal = OutHit.Normal
    InitialTrace_ImpactPoint.Z = baseLocation.Z
    startVector =  InitialTrace_ImpactPoint + InitialTrace_Normal * -15
    endVector = startVector + UE4.FVector(0 , 0 , TraceSettings.MaxLedgeHeight + TraceSettings.DownwardTraceRadius + 1)
    UE4.UKismetSystemLibrary.SphereTraceSingle(WorldContext, startVector , endVector,
    TraceSettings.DownwardTraceRadius , halfHeight , UE4.ETraceTypeQuery.Climbable, false , nil ,DebugType , OutHit , true)
    bWalkAble = self.Pawn.CharacterMovement:IsWalkable(OutHit)
    if not bWalkAble or not OutHit.bBlockingHit then 
        return false
    end
    local DownTraceLocation =  UE4.FVector(OutHit.Location.X , OutHit.Location.Y , OutHit.ImpactPoint.Z )
    self.HitComponent = OutHit.HitComponent
    local Location = self:GetCapsuleLocationfromBase(DownTraceLocation , 2.0)
    local hasRoom = self:CapsuleHasRoomCheck(self.Pawn.CapsuleComponent , Location , 0.0 , 0.0 , DebugType)
    if hasRoom then 
        return false
    end
    local Rotation = UE4.UKismetSystemLibrary.Conv_VectorToRotator(InitialTrace_Normal * UE4.FVector( -1 , -1 , 0))
    self.transform = UE4.UKismetSystemLibrary.MakeTransform( Location , Rotation , UE4.FVector(1 , 1, 1))
    self.MantleHeight = (Location - self.Pawn:K2_GetActorLocation()).Z

    return true
end

function class:MantleStart()
    local MantleAsset = self:GetMantleAsset()
    
end

function class:CapsuleHasRoomCheck(Capsule , TargetLocation , HeightOffset , RadiusOffset , DebugType)
    local halfHeight = Capsule:GetScaledCapsuleHalfHeight_WithoutHemisphere()
    local z = RadiusOffset * -1 + halfHeight  + HeightOffset
    local startVector = TargetLocation + UE4.FVector(0 , 0 , z)
    local endVector = TargetLocation - UE4.FVector(0 , 0 , z)
    local radius = Capsule.CapsuleRadius + RadiusOffset
    local OutHit = nil
    local bHit = UE4.UKismetSystemLibrary.SphereTraceSingleByProfile(gWorld:getWorldContext() , startVector , endVector,
    radius , "ALS_Character" , false , nil ,DebugType , OutHit , true)
    return bHit and not ( OutHit.bBlockingHit or  OutHit.bStartPenetrating)
end

function class:GetMantleAsset()
    local Mantle_Asset = UE4.FMantle_Asset()
    Mantle_Asset.PositionCorrectionCurve = 1
    Mantle_Asset.StartingOffset = UE4.FVector(0 , 65 , 200)
    Mantle_Asset.LowHeight = 50
    Mantle_Asset.LowPlayRate = 1
    Mantle_Asset.LowStartPosition = 0.5
    Mantle_Asset.HighHeight = 100
    Mantle_Asset.HighPlayRate = 1
    Mantle_Asset.HighStartPosition = 0
    return Mantle_Asset
end
return class