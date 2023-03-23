require "Network.ProtoDown"
require "Network.ProtoUp"
local ProtoId = require "Network.EProtoId"

local class = class(GA.Network, "Pbc")
local Promise = GA.Utility.Promise

local _pb = require "pb"
local _pb_path = gRootPath .. "\\Proto\\pb\\"
local _pb_proto = {}
local _proto_map = {}
local _wrapType = "pb.WrapMessage"
function class:ctor()
    self.reg()
    self.down = GA.Network.ProtoDown.new()
    self.up = GA.Network.ProtoUp.new()
    for k, v in pairs(ProtoId) do
        _pb_proto[v] = {name = k , pb = "pb." .. k , id = v}
    end
end
local function _regFile(file)
    local ret = _pb.loadfile(_pb_path .. file)
    if not ret then
        logE(file .. " load failed :_regFile")
    end
end

function class.reg()
    -- pbc reg auto-gen
    _regFile('Cmd.pb')
    _regFile('DataConfig.pb')
    _regFile('Login.pb')
    _regFile('MessageType.pb')
    _regFile('Wrap.pb')
    -- pbc reg auto-gen
end
function class.RegisterHandle(sequence, handle)
    _proto_map[sequence] = handle
end
function class.Send(...)
    proto_send(...)
end
function class.recvWrapper(data, id)
    local proto = _pb_proto[id]
    local wrap = _pb.decode(_wrapType, data)
    local msg = _pb.decode(proto.pb, wrap.content)
    local globalHandle = pbc.down[proto.name]
    local response = wrap.response
    local handle = _proto_map[response]
    _proto_map[response] = nil
    local next = true
    if handle then 
        next = handle(msg)
    end
    if next and globalHandle then 
        globalHandle(msg)
    end
end
function class.recv(data, type, id)
    local status, err = pcall(function()
        class.recvWrapper(data, type, id)
    end)
    if not status then
        logE(err)
    end
end

function class.Cmd2Proto(cmd)
    local id = ProtoId[cmd]
    return _pb_proto[id]
end

function class.Encode(msg, pb)
    return _pb.encode(pb, msg)
end
function class.EncodeWrap(wrap)
    return _pb.encode(_wrapType, wrap)
end
local config_path = gRootPath .. "Table/%s.ini"
function class.EncodeConfig(msg, pbname, path)
    if not msg then
        return
    end
    path = path or string.format(config_path, pbname)
    local config = _pb.encode("pb." .. pbname, msg)
    if not config or config == "" then
        logE("EncodeConfig failed: " .. pbname, msg)
        return
    end
    local wf = io.open(path, "wb")
    wf:write(config)
    wf:close()
end

function class.DecodeConfig(pbname, path)
    path = path or string.format(config_path, pbname)
    local rf = io.open(path, "rb")
    local data = rf:read("*a")
    rf:close()
    local msg = _pb.decode("pb." .. pbname, data)
    return msg
end
