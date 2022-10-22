local BpType = GA.Config.BpType or {}
local BpClassMap = {
	-- bpmap reg auto-gen
	-- ../../../../../ouczbs/Survive/Content/\Blueprints start
	BP_LuaManager = BpType.BP_LuaManager ,
	BP_MessageManager = BpType.BP_MessageManager ,
	UI_AndriodWindow = BpType.UI_AndriodWindow ,
	-- ../../../../../ouczbs/Survive/Content/\Blueprints end

	-- ../../../../../ouczbs/Survive/Content/\AdvancedLocomotionV4\Blueprints start
	ALS_AnimMan_CharacterBP = BpType.ALS_AnimMan_CharacterBP ,
	ALS_Base_CharacterBP = BpType.ALS_Base_CharacterBP ,
	-- ../../../../../ouczbs/Survive/Content/\AdvancedLocomotionV4\Blueprints end

	-- ../../../../../ouczbs/Survive/Content/\PlayerBuildingSystem\Blueprints start
	BP_BuildingAbility = BpType.BP_BuildingAbility ,
	BP_CeilingGrid = BpType.BP_CeilingGrid ,
	BP_DoorGrid = BpType.BP_DoorGrid ,
	BP_FoundationGrid = BpType.BP_FoundationGrid ,
	BP_MasterGrid = BpType.BP_MasterGrid ,
	BP_PillerGrid = BpType.BP_PillerGrid ,
	BP_StairsGrid = BpType.BP_StairsGrid ,
	BP_WallGrid = BpType.BP_WallGrid ,
	BP_WindowGrid = BpType.BP_WindowGrid ,
	BP_DoorFrame_01 = BpType.BP_DoorFrame_01 ,
	BP_MasterBuildPart = BpType.BP_MasterBuildPart ,
	BP_WindowFrame_01 = BpType.BP_WindowFrame_01 ,
	BP_BuildMaster = BpType.BP_BuildMaster ,
	-- ../../../../../ouczbs/Survive/Content/\PlayerBuildingSystem\Blueprints end

	-- ../../../../../ouczbs/Survive/Content/\TouchSystem\Blueprints start
	UI_TouchWindow = BpType.UI_TouchWindow ,
	-- ../../../../../ouczbs/Survive/Content/\TouchSystem\Blueprints end

	-- bpmap reg auto-gen

	-- sbpmap reg auto-gen

	-- sbpmap reg auto-gen
	SkeletalMesh = "SkeletalMesh",
	StaticMeshComponent = "StaticMeshComponent",
	StaticMesh = "StaticMesh",
	LandScape = "Landscape",
}


local GeneratedBpClassMap = setmetatable({}, {__mode = "v"})

function GA:loadBpClass()
	local mt = {
		__index = function(t, k)
			if not GeneratedBpClassMap[k] then
				if BpClassMap[k] then 
					GeneratedBpClassMap[k] = import(BpClassMap[k])
				elseif BpType[k] then 
					GeneratedBpClassMap[k] = import(BpType[k])
				end 
			end
			return GeneratedBpClassMap[k]
		end
	}
	self.BpClass = setmetatable({}, mt)
end
GA:loadBpClass()
