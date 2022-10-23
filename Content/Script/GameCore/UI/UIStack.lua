local class = class(GA.UI, "UIStack")

function class:ctor(layer)
	self.m_UIBaseArray	   = {}
	self.layer = layer
end
local function _findUIWindow(windowArray , uiData)
	for index ,window in ipairs(windowArray) do 
		if window.__uid == uiData.id then 
			return window , index
		end
	end
end
function class:openUIWindowWithClass(uiData, inIsKeepOther)
	local tWindow , tIndex = _findUIWindow(self.m_UIBaseArray , uiData)
	if tWindow == nil then
		local layout = import(uiData.layout)
		tWindow = UE.UWidgetBlueprintLibrary.Create(gWorld:getWorldContext() , layout)
		tWindow:AddToViewport(self.layer)
		if not tWindow.Object then 
			local uobject = tWindow
			tWindow = GA.UI.UIWindowBP.new(uobject)
		end
		tWindow:init(uiData)
	end
	return self:openUIInternal(tWindow, inIsKeepOther, tIndex)
end

function class:openUIInternal(inWindow, inIsKeepOther, inInternalIndex)
	local tIsLast = inInternalIndex == #self.m_UIBaseArray
	if tIsLast then 
		self:showWindow(inWindow)
		return inWindow
	end
	if inInternalIndex then
		table.remove(self.m_UIBaseArray, inInternalIndex)
	end
	local tCurrentUICount = #self.m_UIBaseArray
	if inWindow.s_bClearSelfStack then
		self:clearUIWindows()
	elseif tCurrentUICount ~= 0 and not inIsKeepOther then
		self:hideUIWindow(self.m_UIBaseArray[tCurrentUICount])
	end
	table.insert(self.m_UIBaseArray, inWindow)
	self:showWindow(inWindow)
	return inWindow
end

function class:showWindow(window)
	window:show()
end

function class:clearUIWindows()
	for _,window in ipairs(self.m_UIBaseArray) do 
		window:destroy(bUIManager)
	end 
	self.m_UIBaseArray = {}
end
function class:hideUIWindow(window)
	window:hide()
end
function class:closeUIWindow(uiData)
	window:hide()
end