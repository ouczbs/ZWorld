

---@type FunBtnEntry
local class = UnLua.Class(GA.UI.UIEntry)
GA.UI.PublicFunBtnEntry = class
function class:Construct()
	
end
function class:OnListItemObjectSet(item)
    local data = UE.GetLuaData(item)
    self.item = item
    self.data = data
    self.Text:SetText(data.text)
    self:OnRefreshSelectedState()
end
function class:OnRefreshSelectedState()
    
end
function class:BP_OnItemSelectionChanged(bIsSelected)
    self.item.bIsSelected = bIsSelected
    self:OnRefreshSelectedState()
end
return class