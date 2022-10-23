
local class = class(GA.Manager, "BuildingManager" )


function class:ctor()

end
function class:init()
    self.buildingAbility = gWorld:spawnActor(GA.BpClass.BP_BuildingAbility, UE.FVector(0.0, 0.0, 0.0) , UE.FRotator(0, 0, 0))
end
--GA:AddInitManager(class.__cname , class)
return class