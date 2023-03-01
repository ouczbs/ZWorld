local class = class(GA.UI, "UIManager")
local _Gui = nil
local _UICheck = nil
function class:ctor()
    self.m_UiStack = {}
end

function class:init()
    _Gui = GA.Config.Gui
    _UICheck = GA.Config.UICheck
end
function class:openUIWindowWithId(id, state, bKeepOther)
    local uiData = _Gui:getItemById(id)
    if not uiData then return end
	if not _UICheck(id, state) then
        return
    end
    local layer = uiData.layer
    if not self.m_UiStack[layer] and layer then 
        self.m_UiStack[layer] = GA.UI.UIStack.new(layer)
    end
    local retUI = self.m_UiStack[uiData.layer]:openUIWindowWithClass(uiData, state, bKeepOther or false)
    return retUI
end
function class:closeUIWindow(id)
    local uiData = _Gui:getItemById(id)
    if not uiData then return end
    local layer = uiData.layer
    self.m_UiStack[layer]:closeUIWindow(uiData)
end