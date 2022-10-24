

---@type LoginWindow
local class = UnLua.Class(GA.UI.UIWindow)
GA.UI.LoginWindow = class
function class:Construct()
	self.EnterGameBtn.OnClicked:Add(self, self.OnClicked_EnterGameBtn)
	local controller = gWorld:getMainController()
	UE.UWidgetBlueprintLibrary.SetInputMode_UIOnlyEx(controller , nil , UE.EMouseLockMode.DoNotLock)
end

function class:OnClicked_EnterGameBtn()
	gWorld.UIManager:closeUIWindow("Login")
	gWorld.UIManager:openUIWindowWithName("Main")
	local controller = gWorld:getMainController()
	UE.UWidgetBlueprintLibrary.SetInputMode_GameAndUIEx(controller, nil , UE.EMouseLockMode.DoNotLock , true)
end

return class