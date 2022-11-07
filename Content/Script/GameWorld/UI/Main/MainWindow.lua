

---@type MainWindow
local class = UnLua.Class(GA.UI.UIWindow)
GA.UI.MainWindow = class
function class:Construct()
    local dataList = GA.Config.FunBtn:toEntryData()
    for k,v in ipairs(dataList) do 
        local item = gWorld.UGamePoolSubsystem:Spawn(UE.ULuaUIEntry)
        UE.SetLuaData(item , v)
        self.ListView_Top:AddItem(item)
    end
    self.ListView_Top:SetScrollBarVisibility(UE.ESlateVisibility.Collapsed)
    self.ListView_Top.BP_OnItemSelectionChanged:Add(self , self.BP_OnItemSelectionChanged)
end
function class:BP_OnItemSelectionChanged(item , bIsSelected)
    local data = UE.GetLuaData(item)
    if self.selectItem then 
        self.selectItem.bIsSelected = false
    end
    item.bIsSelected =  true
    self.selectItem = item
end

return class