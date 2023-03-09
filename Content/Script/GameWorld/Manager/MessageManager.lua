--lua class : test_C

local class = Class(GA.Manager, "MessageManager")

function class:init()
    self:RegisterToGame()
end
return class

