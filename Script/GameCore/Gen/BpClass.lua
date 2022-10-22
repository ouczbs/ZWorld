local BpType = GA.BpType or {}
local BpClassMap = {
	-- bpmap reg auto-gen
	-- ../../../../../ouczbs/ZWorld/Content/\Blueprints start
	BP_BasePlayAnim = BpType.BP_BasePlayAnim ,
	BP_OverLayAnim = BpType.BP_OverLayAnim ,
	BP_PlayAnim = BpType.BP_PlayAnim ,
	BP_PlayCharacter = BpType.BP_PlayCharacter ,
	BP_PlayCharacterBase = BpType.BP_PlayCharacterBase ,
	BP_PlayerController = BpType.BP_PlayerController ,
	BP_PlayerState = BpType.BP_PlayerState ,
	BP_GameOwner = BpType.BP_GameOwner ,
	UI_EditorAnimRetarget = BpType.UI_EditorAnimRetarget ,
	UI_FoldPanel = BpType.UI_FoldPanel ,
	UI_SourceComboBox = BpType.UI_SourceComboBox ,
	-- ../../../../../ouczbs/ZWorld/Content/\Blueprints end

	-- ../../../../../ouczbs/ZWorld/Content/\AdvancedLocomotionV4\Blueprints start
	ALS_AnimMan_CharacterBP = BpType.ALS_AnimMan_CharacterBP ,
	ALS_Base_CharacterBP = BpType.ALS_Base_CharacterBP ,
	-- ../../../../../ouczbs/ZWorld/Content/\AdvancedLocomotionV4\Blueprints end

	-- ../../../../../ouczbs/ZWorld/Content/\AdvancedVillagePack\Blueprints start
	BP_Butterfly = BpType.BP_Butterfly ,
	BP_CampFire = BpType.BP_CampFire ,
	BP_CampFire_OnDayOnNight = BpType.BP_CampFire_OnDayOnNight ,
	BP_House_Var01 = BpType.BP_House_Var01 ,
	BP_House_Var01_OnDayOnNight = BpType.BP_House_Var01_OnDayOnNight ,
	BP_House_Var02 = BpType.BP_House_Var02 ,
	BP_House_Var02_OnDayOnNight = BpType.BP_House_Var02_OnDayOnNight ,
	BP_Street_Lamp = BpType.BP_Street_Lamp ,
	BP_Street_Lamp_OnDayOnNight = BpType.BP_Street_Lamp_OnDayOnNight ,
	BP_Tree = BpType.BP_Tree ,
	BP_Well = BpType.BP_Well ,
	BP_Interface_OnDayOnNight = BpType.BP_Interface_OnDayOnNight ,
	BP_Misc_DayNight_Cycle = BpType.BP_Misc_DayNight_Cycle ,
	BP_Misc_Text = BpType.BP_Misc_Text ,
	-- ../../../../../ouczbs/ZWorld/Content/\AdvancedVillagePack\Blueprints end

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
				else
					GeneratedBpClassMap[k] = import(k)
				end 
			end
			return GeneratedBpClassMap[k]
		end
	}
	self.BpClass = setmetatable({}, mt)
end
GA:loadBpClass()
