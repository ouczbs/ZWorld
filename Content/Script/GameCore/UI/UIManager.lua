local class = class(GA.UI, "UIManager")
local _UiList = {}
local _UiIdCacheList = {}
function class:ctor()
    self.m_UiStack = {}
end

function class:init()
    _UiList = GA.Config.Gui:getItemList()
end

function class:openUIWindowWithName(name, bKeepOther)
    local uiData = _UiList[name]
    local layer = uiData.layer
    uiData.name = name
    if not self.m_UiStack[layer] and layer then 
        self.m_UiStack[layer] = GA.UI.UIStack.new(layer)
    end
	local retUI = self.m_UiStack[layer]:openUIWindowWithClass(uiData, bKeepOther or false)
    return retUI
end
function class:openUIWindowWithId(id, bKeepOther)
    local uiData = _UiIdCacheList[id]
    if not uiData then 
        for k,v in pairs(_UiList) do 
            if v.id == id then 
                uiData = v
                break
            end
        end
    end
    local layer = uiData.layer
    if not self.m_UiStack[layer] and layer then 
        self.m_UiStack[layer] = GA.UI.UIStack.new(layer)
    end
	local retUI = self.m_UiStack[layer]:openUIWindowWithClass(uiData, bKeepOther or false)
    return retUI
end
function class:closeUIWindow(window)
    local uiData = _UiList[window.__cname]
    local layer = uiData.layer
    self.m_UiStack[layer]:closeUIWindow(uiData)
end