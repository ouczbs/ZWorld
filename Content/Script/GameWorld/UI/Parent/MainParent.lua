

---@type MainParent
local class = UnLua.Class(GA.UI.UIParent)
GA.UI.MainParent = class
function class:Construct()
    logE(self.GridPanel, "MainParent")
end
function class:onAddChildWindow(child)
    local slot = self.MainPanel:AddChildToCanvas(child)
    slot:SetLayout(self.LayoutData)
end
return class