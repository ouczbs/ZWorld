GA.Request = {}
local mt = {
    __index = function(t, k)
        return k
    end
}
setmetatable(GA.Request, mt)