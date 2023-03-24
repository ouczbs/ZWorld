local super = GA.UI.ItemList
local class = class(GA.UI, "TileView", super)
function class:Resize (luaclass, ListView)
    self.ListView = ListView
    ListView:SetScrollBarVisibility(UE.ESlateVisibility.Collapsed)
    ListView.BP_OnItemSelectionChanged:Add(luaclass, self.BP_OnItemSelectionChanged)
end
