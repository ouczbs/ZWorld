

---@type ItemBagWindow
local class = UnLua.Class(GA.UI.UIWindow)
GA.UI.ItemBagWindow = class
local function printslot(slot)
    if not slot then return end
    local lay = slot:GetLayout()
    local anch = slot:GetAnchors()
    local pos = slot:GetPosition()
    local size = slot:GetSize()
    slot:SetSize(UE.FVector2D(1000,1000))
    local off = slot:GetOffsets()
    local alig = slot:GetAlignment()
    local autosize = slot:GetAutoSize()
    local zorder = slot:GetZOrder()
    logE(slot)
    logE(lay , anch , pos , size)
    logE(off , alig , autosize , zorder)
end
function class:Construct()
    logE(self.GridPanel, "ItemBagWindow")
    local _UiList = GA.Config.Gui:getItemList()
    local uiData = _UiList.BaseWindow
	local layout = LoadClass(uiData.layout)
	local tWindow = NewObject(layout, gWorld:getWorldContext(), nil, uiData.script)
    local slot = self.MainPanel:AddChildToCanvas(tWindow)
    local sslot = self.MainPanel.Slot
    --tWindow:set
    printslot(slot)
    printslot(sslot)
end

return class