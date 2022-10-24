local rawget = _G.rawget
local rawset = _G.rawset
local rawequal = _G.rawequal
local type = _G.type
local getmetatable = _G.getmetatable
local require = _G.require

local GetUProperty = GetUProperty
local SetUProperty = SetUProperty

local NotExist = {}

local function Index(t, k)
    local mt = getmetatable(t)
    local super = mt
    while super do
        local v = rawget(super, k)
        if v ~= nil and not rawequal(v, NotExist) then
            rawset(t, k, v)
            return v
        end
        super = rawget(super, "Super")
    end

    local p = mt[k]
    if p ~= nil then
        if type(p) == "userdata" then
            return GetUProperty(t, p)
        elseif type(p) == "function" then
            rawset(t, k, p)
        elseif rawequal(p, NotExist) then
            return nil
        end
    else
        rawset(mt, k, NotExist)
    end

    return p
end

local function NewIndex(t, k, v)
    local mt = getmetatable(t)
    local p = mt[k]
    if type(p) == "userdata" then
        return SetUProperty(t, p, v)
    end
    rawset(t, k, v)
end
local function Class(super)
    local new_class = {}
    local super_class = nil
    if type(super) == "table" then  --lua class
        for k,v in pairs(super) do 
            new_class[k] = v
        end
    elseif super ~= nil then -- c++ class
        super_class = require(super)
    end
    new_class.__index = Index
    new_class.__newindex = NewIndex
    new_class.Super = super_class

  return new_class
end
local function import(resource)
	return UE.UClass.Load(resource)
end
_G.import = import
UnLua.Class = Class