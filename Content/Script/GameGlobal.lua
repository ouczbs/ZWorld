
local function UClass_index(t, k)
	local v = rawget(t, k)
	if v then
		return v
    end
	RegisterClass(k)
	v = rawget(_G, k)
	rawset(t, k, v)
	rawset(_G, k, nil)
	return v
end

local function UEnum_index(t, k)
	local v = rawget(t, k)
	if v then
		return v
    end
    RegisterEnum(k)
	v = rawget(_G, k)
	rawset(t, k, v)
	rawset(_G, k, nil)
	return v
end
--UE4 = {}
UEnum = {}
--setmetatable(UE4, {__index = UClass_index })
--setmetatable(UEnum, {__index = UEnum_index })

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

function import(resource)
	return UE4.UClass.Load(resource)
end

function CreateGlobalVar()
    gWorld      = GA.World.new()
    gRequest = {}
    pbc = GA.Network.Pbc.new()
    gGameConst      = GA.Config.GameConst
    gLuaType   =  GA.Config.LuaType
    gRefers   =  GA.Config.Refers
end