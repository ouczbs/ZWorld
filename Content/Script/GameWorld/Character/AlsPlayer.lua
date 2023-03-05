
local class = Class()
--GA.Character.ALS_Character = class
function class:Initialize(Initializer)
    
end
function class:ReceiveBeginPlay()
    self:RefreshOverlayObject()
end
function class:OnOverlayModeChanged()
    local OverlayMode = self.OverlayMode
    self:RefreshOverlayLinkedAnimationLayer()
    self:RefreshOverlayObject()
end
function class:OnMantlingStarted(TargetPrimitive, TargetRelativeLocation ,TargetRelativeRotation , MantlingHeight, MantlingType)
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
    self.OverlayAnimationInstanceClass  = OverlayAnimationInstanceClass
end

function class:RefreshOverlayObject()
    -- todo
    --self:AttachOverlayObject()
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

return class