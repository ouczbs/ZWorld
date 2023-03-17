--lua class : test_C

local class = Class(GA.Voxel, "VoxelWorld")

function class:init()
   print("init VoxelWorld", UE.AVoxelWorld , UE.UMMOVoxelGenerator)
   local Generator = NewObject(UE.UMMOVoxelGenerator, gWorld:getWorldContext(), nil, gLuaObject.UMMOVoxelGenerator)
   Generator:init()
   self.VisibleChunksCollisionsMaxLOD = 32
   self:SetGeneratorObject(Generator)
   local mat = LoadObject("/Game/Genshin/Voxel/MI_VoxelQuixel_FiveWayBlend_Inst")
   self.VoxelMaterial = mat
   local info = UE.FVoxelWorldCreateInfo()
   self:CreateWorld(info)
   print(self.Generator, Generator)
end
return class


