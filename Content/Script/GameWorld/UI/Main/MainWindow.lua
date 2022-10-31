

---@type MainWindow
local class = UnLua.Class(GA.UI.UIWindow)
GA.UI.MainWindow = class
function class:Construct()
    local item1 = gWorld.UGamePoolSubsystem:Spawn(UE.ULuaUIEntry)
    item1:SetData("item1")
    local item2 = gWorld.UGamePoolSubsystem:Spawn(UE.ULuaUIEntry)
    item2:SetData("item2")
    local item3 = gWorld.UGamePoolSubsystem:Spawn(UE.ULuaUIEntry)
    item3:SetData("item3")
    self.ListView_Top:AddItem(item1)
    self.ListView_Top:AddItem(item2)
    self.ListView_Top:AddItem(item3)
end
return class