
local class = class(GA.Manager, "BuildingManager" )


function class:ctor()

end
function class:init()
    self.buildingAbility = gWorld:spawnActor(GA.BpClass.BP_BuildingAbility, UE4.FVector(0.0, 0.0, 0.0) , UE4.FRotator(0, 0, 0))
end
GA:AddInitManager(class.__cname , class)
return class