--GameWorld.Subsystem.GameOwnerSubsystem_C
require "UnLua"

local class = Class()

function class:OnSpawnRequest(name)
    return gWorld.RequestTable:SpawnRequest(name)
end
function class:OnInitialize()
    self.InterfaceSpawnRequest:Bind(self , self.OnSpawnRequest)
end
return class