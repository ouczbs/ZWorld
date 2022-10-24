

---@type MainWindow
local class = UnLua.Class(GA.UI.UIWindow)
GA.UI.MainWindow = class
function class:Construct()
    local obj1 = UE.UObject.Load(GA.BpType.UI_FunBtnEntry)
    self.ListView_Top:AddItem(obj1)
end
return class
