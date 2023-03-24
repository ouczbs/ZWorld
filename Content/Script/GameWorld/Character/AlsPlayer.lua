local class = Class()
-- GA.Character.ALS_Character = class
function class:Initialize(Initializer)
    print("Initialize ALS_Character")
end
function class:ReceiveBeginPlay()
    self:RefreshOverlayObject()
end
function class:OnOverlayModeChanged()
    local OverlayMode = self.OverlayMode
    self:RefreshOverlayLinkedAnimationLayer()
    self:RefreshOverlayObject()
end
function class:OnMantlingStarted(TargetPrimitive, TargetRelativeLocation, TargetRelativeRotation, MantlingHeight,
    MantlingType)
    if MantlingType == UE.EAlsMantlingType.Low then
        self:ClearOverlayObject()
    end
end
function class:OnMantlingEnded()
    self:RefreshOverlayObject()
end
function class:OnRagdollingStarted()
    self:ClearOverlayObject()
end
function class:OnRagdollingEnded()
    self:RefreshOverlayObject()
end
function class:RefreshOverlayLinkedAnimationLayer()
    local OverlayAnimationInstanceClass = self.OverlayAnimationInstanceClasses:FindRef(self.OverlayMode)
    if OverlayAnimationInstanceClass then
        self.Mesh:LinkAnimClassLayers(OverlayAnimationInstanceClass)
    end
    self.OverlayAnimationInstanceClass = OverlayAnimationInstanceClass
end

function class:RefreshOverlayObject()
    -- todo
    -- self:AttachOverlayObject()
end
function class:ClearOverlayObject()
    -- todo
    self.OverlayStaticMesh:SetStaticMesh(nil)
    self.OverlaySkeletalMesh:SetStaticMesh(nil, true)
    self.OverlaySkeletalMesh:SetAnimClass(nil)
end
function class:AttachOverlayObject()
    -- todo
    UE.UAlsConstants.HandRightGunVirtualBoneName()
end
-- function class:Q_Pressed()
--     -- local forward = self.Camera:GetForwardVector()
--     -- local start_pos = self.Camera:K2_GetComponentLocation()
--     -- local end_pos = start_pos + forward * 1000
--     -- local TraceChannel = UE.ETraceTypeQuery.Visibility
--     -- local isHit, OutHit = UE.UKismetSystemLibrary.LineTraceSingle(self, start_pos, end_pos, TraceChannel, nil, nil, nil,
--     --     nil, true)
--     local rayStart = self:K2_GetActorLocation()
--     rayStart.Z = 100
--     gWorld.VoxelWorld:RemoveSphere(rayStart, 100)
--     print("Q_Pressed>>>>>>>>>>>>>>")
-- end

-- function class:E_Pressed()
--     local rayStart = self:K2_GetActorLocation()
--     rayStart.Z = 100
--     gWorld.VoxelWorld:AddSphere(rayStart, 100)
--     print("E_Pressed>>>>>>>>>>>>>>")
-- end
return class
