

---@type LoginWindow
local class = UnLua.Class(GA.UI.UIWindow)
GA.UI.LoginWindow = class
function class:Construct()
	self.EnterGameBtn.OnClicked:Add(self, self.OnClicked_EnterGameBtn)
end

function class:OnClicked_EnterGameBtn()
	local window = gWorld.UIManager:openUIWindowWithName("Main")
    
end

return class