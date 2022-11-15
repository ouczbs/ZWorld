

---@type MainWindow
local class = UnLua.Class(GA.UI.UIWindow)
GA.UI.MainWindow = class
function class:Construct()
    self.itemList = GA.UI.ItemList.new(self, self.ListView_Top)
    local dataList = GA.Config.FunBtn:toEntryData()
    self.itemList:refreshFromData(dataList)
end
return class