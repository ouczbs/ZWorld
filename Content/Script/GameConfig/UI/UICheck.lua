local checkFuncs = {}
local Gui = GA.Config.Gui
local UID = Gui.ID
checkFuncs[UID.ItemBag] = function()
    return true
end

local UICheck = function(uid)
    if checkFuncs[uid] then 
        return checkFuncs[uid]()
    end
    --local uiData = Gui:getItemById(uid)
    -- 统一的规则 等级 功能 等等
    return true
end

GA.Config.UICheck = UICheck
