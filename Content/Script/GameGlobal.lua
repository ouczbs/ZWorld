require "UnLuaDefine"
function logE(...)
    UnLua.LogError(...)
end
function GetLanguage(id)
    return id
end
local GA = {
    initManagerList = {}
}
local GW = {}
_G.GA = GA
_G.GW = GW
function GA:AddInitManager(name, UManager)
    self.initManagerList[name] = UManager
end
serpent = require "Network.serpent"
function GA.CreateGlobalVar()
    _print = print
    print = logE
    gRootPath = gRootPath or "../../../Content"
    gGameConst = GA.Config.GameConst
    gLuaObject = GA.Config.LuaObject
    gLuaType = GA.Config.LuaType
    gWorld = GA.World.new()
    pbc = GA.Network.Pbc.new()
    UID = GA.Config.Gui.ID
end
