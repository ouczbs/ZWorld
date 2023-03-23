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
function class:openUIWindowWithClass(uiData, state,  inIsKeepOther)
	local tWindow , tIndex = _findUIWindow(self.m_UIBaseArray , uiData)
	if tWindow == nil then
		local layout = LoadClass(uiData.layout)
		tWindow = NewObject(layout, gWorld:getWorldContext(), nil, uiData.script)
		tWindow:AddToViewport(self.layer)
		if not tWindow.Object then 
			local uobject = tWindow
			tWindow = GA.UI.UIWindowBP.new(uobject)
		end
		tWindow:init(uiData, state)

		local parent = uiData.parent
		if parent then 
			local pWindow = gWorld.UIManager:openUIWindowWithId(parent,nil, inIsKeepOther)
			pWindow:addChildWindow(tWindow)
		end
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
		window:destroy()
	end 
	self.m_UIBaseArray = {}
end
function class:hideUIWindow(window)
	window:hide()
end
function class:closeUIWindow(uiData)
	local tWindow , tIndex = _findUIWindow(self.m_UIBaseArray , uiData)
	if tWindow then
		tWindow:destroy()
		table.remove(self.m_UIBaseArray, tIndex)
	end
end