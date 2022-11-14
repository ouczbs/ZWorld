

---@type FunBtnEntry
local class = UnLua.Class(GA.UI.UIEntry)
GA.UI.FunBtnEntry = class
function class:Construct()
	
end
function class:OnListItemObjectSet(item)
    local data = UE.GetLuaData(item)
    self.item = item
    self.data = data
    self.Icon:SetBrushFromTexture(data:getIconAssert() , true)
    self.Text:SetText(data:getText())
    self:OnRefreshSelectedState()
end
function class:OnRefreshSelectedState()
    local bIsSelected = self.item.bIsSelected
    local color = bIsSelected and UE.FLinearColor(1 , 0, 0, 1) or UE.FLinearColor(0 , 1, 0, 1)
    self.Border:SetBrushColor(color)
end
function class:BP_OnItemSelectionChanged(bIsSelected)
    self.item.bIsSelected = bIsSelected
    self:OnRefreshSelectedState()
    if bIsSelected then
        local data = UE.GetLuaData(self.item)
        data:jumpTo()
    end
end
return class