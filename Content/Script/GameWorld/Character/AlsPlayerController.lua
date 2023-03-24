
local class = Class()
function class:Initialize(Initializer)
    print("Initialize AlsPlayerController")
end
function class:ReceiveBeginPlay()
    if not self:IsLocalController() then 
        return
    end
    UE.UWidgetBlueprintLibrary.SetInputMode_GameOnly(self)
    --UE.EnhancedInputLocalPlayerSubsystem:AddMappingContext()
end
function class:SetGlobalTimeDilation(TimeDilation)
    if UE.UKismetSystemLibrary.IsStandalone() then 
        UE.UGameplayStatics.SetGlobalTimeDilation(TimeDilation)
    end
end
function class:OnOverlayModeChanged(value)
    if value then 
        if not self.bSlomoActive then 
            self:SetGlobalTimeDilation(0.35)
        end
        self.OverlayModeMenuWidget:AddToViewport()
    else 
        if not self.bSlomoActive then 
            self:SetGlobalTimeDilation(1.0)
        end
        self.OverlayModeMenuWidget:ApproveOverlayMode()
        self.OverlayModeMenuWidget:RemoveFromParent()
    end
end
function class:OnNextOverlayMode()
    if self.OverlayModeMenuWidget:IsInViewport() then 
        self.OverlayModeMenuWidget:SelectNextOverlayMode()
    end
end
function class:OnToggleUI()
    self.bUIVisible = not self.bUIVisible

end
function class:OnSlomo()
    self.bSlomoActive = not self.bSlomoActive
    self:SetGlobalTimeDilation(self.bSlomoActive and 0.15 or 1.0)
end
return class
