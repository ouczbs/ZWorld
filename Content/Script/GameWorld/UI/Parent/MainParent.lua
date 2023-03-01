

---@type MainParent
local class = UnLua.Class(GA.UI.UIParent)
GA.UI.MainParent = class
function class:Construct()
    logE(self.GridPanel, "MainParent")
    self.itemList = GA.UI.ItemList.new(self, self.ListView_Slide)
    --getUIListByID
end
function class:updateChildUId(child)
    if self.childUId == child.__uid then return end
    if self.childUId then 
        gWorld.UIManager:closeUIWindow(self.childUId)
        self.MainPanel:RemoveChildAt(0)
    end
    self.childUId = child.__uid
    return true
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
    if not self:updateChildUId(child) then 
        return
    end
    local slot = self.MainPanel:AddChildToCanvas(child)
    slot:SetLayout(self.LayoutData)
    self:updateUIList(child)
end

return class