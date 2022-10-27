

---@type MainWindow
local class = UnLua.Class(GA.UI.UIWindow)
GA.UI.MainWindow = class
function class:Construct()
    local item = UE.FUIItemData()
    item.tat = 1
    print(item.IsSelected)
    print(item.tat)
    print("?????????")
    --self.ListView_Top:AddItem(item)
end
return class
