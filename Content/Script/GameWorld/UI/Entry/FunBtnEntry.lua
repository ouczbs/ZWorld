

---@type FunBtnEntry
local class = UnLua.Class(GA.UI.UIEntry)
GA.UI.FunBtnEntry = class
function class:Construct()
	
end

function class:OnListItemObjectSet(object)
	logE(object)
    local str = object:GetData()
    logE("call OnListItemObjectSet getdata = " .. str)
end

return class