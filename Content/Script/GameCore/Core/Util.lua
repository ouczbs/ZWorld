
local InscSequence = class(GA.Core,"InscSequence")


function InscSequence:ctor(seed)
    self.seed = seed
end

function InscSequence:insc(seed)
    seed = seed or self.seed
    self.seed = seed + 1
    return seed
end
