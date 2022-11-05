

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
    local color = nil
    if self.item.bIsSelected then 
        color = UE.FLinearColor(1 , 0, 0, 1)
    else 
        color = UE.FLinearColor(0 , 1, 0, 1)
    end
    self.Border:SetBrushColor(color)
end
function class:BP_OnItemSelectionChanged(bIsSelected)
    logE( "ItemEntry " , self.data.id , bIsSelected)
    self.item.bIsSelected = bIsSelected
    self:OnRefreshSelectedState()
end
return class