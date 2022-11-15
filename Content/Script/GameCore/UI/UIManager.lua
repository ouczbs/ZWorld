local class = class(GA.UI, "UIManager")
local _Gui = {}
local _UICheck = nil

function class:ctor()
    self.m_UiStack = {}
end

function class:init()
    _Gui = GA.Config.Gui
    _UICheck = GA.Config.UICheck
end
function class:_openUIWindow(uiData , bKeepOther)
    if not  _UICheck(uiData.id) then
        return
    end
    local retUI = self.m_UiStack[uiData.layer]:openUIWindowWithClass(uiData, bKeepOther or false)
    return retUI
end
function class:openUIWindowWithName(name, bKeepOther)
    local uiData = _Gui:getItemByName(name)
    if not uiData then return false end
    local layer = uiData.layer
    if not self.m_UiStack[layer] and layer then 
        self.m_UiStack[layer] = GA.UI.UIStack.new(layer)
    end
    return self:_openUIWindow(uiData , bKeepOther)
end
function class:openUIWindowWithId(id, bKeepOther)
    local uiData = _Gui:getItemById(id)
    if not uiData then return false end
    local layer = uiData.layer
    if not self.m_UiStack[layer] and layer then 
        self.m_UiStack[layer] = GA.UI.UIStack.new(layer)
    end
	return self:_openUIWindow(uiData , bKeepOther)
end
function class:closeUIWindow(name)
    local uiData = _Gui:getItemByName(name)
    if not uiData then return end
    local layer = uiData.layer
    self.m_UiStack[layer]:closeUIWindow(uiData)
end