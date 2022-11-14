
local InscSequence = class(GA.Core,"InscSequence")


function InscSequence:ctor(seed)
    self.seed = seed
end

function InscSequence:insc(seed)
    seed = seed or self.seed
    self.seed = seed + 1
    return seed
end

function InscSequence.Generator(start)
    start = start or 1
    local sequence = GA.Core.InscSequence.new(start)
    local mt = {
        __index = function(t, k)
            local v = rawget(t,k)
            if v then return v end
            v = sequence:insc()
            rawset(t, k, v)
            return v
        end,
    }
    return setmetatable({}, mt)
end