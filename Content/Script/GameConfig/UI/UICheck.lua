local _Scripts = {}
local _Gui = GA.Config.Gui
GA.Config.UICheck = function(id, state)
    local uiclass = _Scripts[id]
    if not uiclass then 
        local uiData = _Gui:getItemById(id)
        uiclass = require(uiData.script)
        _Scripts[id] = uiclass
    end
    if uiclass.onUICheck then 
        return uiclass.onUICheck(state)
    end
    return true
end
