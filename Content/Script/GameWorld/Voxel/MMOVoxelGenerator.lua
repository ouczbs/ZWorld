--lua class : test_C

local class = Class(GA.Voxel, "UMMOVoxelGenerator")
print("UMMOVoxelGenerator")
function class:init()
    self.bLuaObject = true
end
local r = 100
local empty = -100
function class:GetValue(X ,Y ,Z ,LOD)
    if X > r or X < -r then 
        return empty
    end
    if Y > r or Y < -r then 
        return empty
    end
    if Z > r or Z < -r then 
        return empty
    end
    return Z + 0.001
end
function class:GetMaterialType(X ,Y ,Z ,LOD)
    return UE.EVoxelMaterialConfig.RGB
end
return class


