

---@type MainWindow
local class = UnLua.Class(GA.UI.UIWindow)
GA.UI.MainWindow = class
function class:Construct()
    local item1 = gWorld.UGamePoolSubsystem:Spawn(UE.ULuaUIEntry)
    local item2 = gWorld.UGamePoolSubsystem:Spawn(UE.ULuaUIEntry)
    local item3 = gWorld.UGamePoolSubsystem:Spawn(UE.ULuaUIEntry)
    local data = GA.UI.FunBtnEntry.new()
    UE.SetLuaData(item1 , data)
    self.ListView_Top:AddItem(item1)
    self.ListView_Top:AddItem(item2)
    self.ListView_Top:AddItem(item3)
end
return class