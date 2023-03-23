-- This is a cmd desc file auto gen from origin-proto.
-- Please do no modification.

-- local MOVE_USERCMD = 2 * 256 --移动指令
-- local DATA_USERCMD = 3 * 256 --数据指令
local MAP_USERCMD = 4 * 256 -- 地图指令
local LOGIN_USERCMD = 5 * 256 --登录指令

local EProtoId = {
    MapUserInfoCmd = MAP_USERCMD + 1,
    
    LoginAccountCmd = LOGIN_USERCMD + 1,
    LoginAccountAckCmd = LOGIN_USERCMD + 2,
}
return EProtoId
