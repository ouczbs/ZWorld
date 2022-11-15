

---@type MainParent
local class = UnLua.Class(GA.UI.UIParent)
GA.UI.MainParent = class
function class:Construct()
    logE(self.GridPanel, "MainParent")
    self.itemList = GA.UI.ItemList.new(self, self.ListView_Slide)
    --getUIListByID
end
function class:removeBefore(child)
    if self.childName then 
        gWorld.UIManager:closeUIWindow(self.childName)
        self.MainPanel:RemoveChildAt(0)
        self.childName = child.__name
    end
end
function class:updateUIList(child)
    local uid = child.__uid
    local uiList,type = GA.Config.PublicFun:getUIListByID(uid)
    if self.type == type then 
        return
    end
    self.uiList = uiList
    self.type = type
    self.itemList:refreshFromData(uiList)
end
function class:onAddChildWindow(child)
    if self.childName == child.__name then return end
    self:removeBefore(child)
    local slot = self.MainPanel:AddChildToCanvas(child)
    slot:SetLayout(self.LayoutData)
    self:updateUIList(child)
end

return class