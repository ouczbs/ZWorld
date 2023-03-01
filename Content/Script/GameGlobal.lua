require "UnLuaDefine"
function logE(...)
	UnLua.LogError(...)
end
local GA = {
	initManagerList = {} ,
}
local GW = {

}
_G.GA = GA
_G.GW = GW
function GA:AddInitManager(name , UManager) 
	self.initManagerList[name] = UManager
end
serpent = require "Network.serpent"
function GA.CreateGlobalVar()
    gRequest = {}
    gRootPath = gRootPath or "../../../Content"
    gGameConst      = GA.Config.GameConst
    gLuaType   =  GA.Config.LuaType
    gRefers   =  GA.Config.Refers
    gWorld      = GA.World.new()
    pbc = GA.Network.Pbc.new()
    UID = GA.Config.Gui.ID
end