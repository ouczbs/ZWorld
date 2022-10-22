--GameWorld.Ultimate_Traversal_Anims.Maps.TestMap_C
--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--
require "UnLua"
local KismetMathLibrary = UE4.UKismetMathLibrary
local class = Class()
function class:PrintActor(Character)
    local Acceleration = Character.CharacterMovement:GetCurrentAcceleration()
    local Velocity = Character:GetVelocity()
    local Rotation = Character:K2_GetActorRotation()
    local Location = Character:K2_GetActorLocation()
    print(Acceleration , Velocity)
    --print(Rotation , Location)
end


function class:CalcVelocity(Character , DeltaTime)
    local Friction = 8
    local Acceleration = Character.CharacterMovement:GetCurrentAcceleration()
    local AccelDir = KismetMathLibrary.Normal(Acceleration , 0.1)
    local Velocity = Character:GetVelocity()
    local VelSize = KismetMathLibrary.VSize(Velocity)
    print(AccelDir , VelSize ) 
    print(Velocity)
    local Velocity2 = Velocity - (Velocity - AccelDir * VelSize) * DeltaTime * Friction
    print(Velocity2)
end
function class:MoveCircle(Character , Radiu , Center , Dt)
    local Angle = self.Time * self.AngleSpeed
    local Direction = UE4.FVector(KismetMathLibrary.Sin(Angle) , - KismetMathLibrary.Cos(Angle) , 0)
    Character:AddMovementInput(Direction , 1)
    --print(self.PlayerCharacter_C_1_ExecuteUbergraph_TestMap_RefProperty)
    --.PlayerCharacter_C_1
    --self:CalcVelocity(Character , dt)
    local DirectionAgree = self:CalculateDirection(Character)
    self:MakeMovement(Character , DirectionAgree , 100)
    self:PrintActor(Character)
end
function class:MoveCircle2(Character , Radiu , Center , Dt)
    local Angle = self.Time * self.AngleSpeed
    local X = Center.X - Radiu * KismetMathLibrary.Sin(Angle)
    local Y = Center.Y + Radiu * KismetMathLibrary.Cos(Angle)
    local Location = Character:K2_GetActorLocation()
    local Position = UE4.FVector(X , Y , Location.Z)
    Character:K2_SetActorLocation(Position)
    local degree = Angle * 180 / KismetMathLibrary.GetPI() + 180
    local Rotation = Character:K2_GetActorRotation()
    Rotation.Yaw = degree
    Character:K2_SetActorRotation(Rotation)
    local Velocity = (Position - Location) / Dt
    Velocity = KismetMathLibrary.Normal(Velocity , 0.1)
    local RealitiveVelocity = KismetMathLibrary.LessLess_VectorRotator(Velocity , Rotation)
    local Agree = KismetMathLibrary.DegAsin(RealitiveVelocity.Y)
    self:MakeMovement(Character , Agree , 100)
end
function class:CalculateDirectionAgree(Character)
    local Velocity = Character:GetVelocity()
    Velocity = KismetMathLibrary.Normal(Velocity , 0.1)
    local Rotation = Character:K2_GetActorRotation()
    local RealitiveVelocity = KismetMathLibrary.LessLess_VectorRotator(Velocity , Rotation)
    local Agree = KismetMathLibrary.Acos(RealitiveVelocity.X)
    return Agree
end
function class:MakeMovement(Character , Direction , Speed)
    local Anim = Character.Mesh:GetAnimInstance()
    Anim.Direction = Direction
    Anim.Speed = Speed
end

-- function class:ReceiveTick(DeltaSeconds)
-- end

--function class:ReceiveAnyDamage(Damage, DamageType, InstigatedBy, DamageCauser)
--end

--function class:ReceiveActorBeginOverlap(OtherActor)
--end

--function class:ReceiveActorEndOverlap(OtherActor)
--end

return class
