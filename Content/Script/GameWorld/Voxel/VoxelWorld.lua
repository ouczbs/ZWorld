--lua class : test_C

local class = Class(GA.Voxel, "VoxelWorld")

function class:init()
   print("init VoxelWorld", UE.AVoxelWorld , UE.UMMOVoxelGenerator)
   self:SetGeneratorClass(UE.UMMOVoxelGenerator.StaticClass())
   local mat = LoadObject("/Game/Genshin/Voxel/MI_VoxelQuixel_FiveWayBlend_Inst")
   self.VoxelMaterial = mat
   local info = UE.FVoxelWorldCreateInfo()
   self:CreateWorld(info)
   print(self, voxelGenerator)
end
return class


