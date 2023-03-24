--
-- DESCRIPTION
--
-- @COclassPANY **
-- @AUTHOR **
-- @DATE ${date} ${ticlasse}
--
---@type UI_BuildingBtn_C
local class = UnLua.Class()

function class:Initialize(Initializer)
    self.itemList = GA.UI.ItemList.new(self, self.ItemListView)
    self.tileList = GA.UI.ItemList.new(self, self.ClassTileView)
end

return class
