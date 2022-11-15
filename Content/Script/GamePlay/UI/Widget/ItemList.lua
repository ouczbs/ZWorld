

local class = class(GA.UI, "ItemList")
function class:ctor(luaclass , ListView)
    self.ListView = ListView
    ListView:SetScrollBarVisibility(UE.ESlateVisibility.Collapsed)
    ListView.BP_OnItemSelectionChanged:Add(luaclass , self.BP_OnItemSelectionChanged)
 end
function class:refreshFromData(dataList)
    local ListView = self.ListView
    local count = ListView:GetNumItems() + 1
    local newCount = #dataList
    local min = math.min(count , newCount)
    for k = 1 , min do 
        local item = ListView:GetItemAt(k - 1)
        UE.SetLuaData(item , dataList[k])
    end
    for k = min,count do 
        local item = ListView:GetItemAt(k - 1)
        ListView:RemoveItem(item)
        gWorld.UGamePoolSubsystem:Unspawn(item)
    end
    for k = min,newCount do 
        local item = gWorld.UGamePoolSubsystem:Spawn(UE.ULuaUIEntry)
        UE.SetLuaData(item , dataList[k])
        ListView:AddItem(item)
    end
    ListView:RequestRefresh()
end
function class:BP_OnItemSelectionChanged(item)
    if self.selectItem then 
        self.selectItem.bIsSelected = false
    end
    item.bIsSelected =  true
    self.selectItem = item
end