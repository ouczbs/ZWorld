local BpType = GA.BpType or {}
local BpClassMap = {
	-- bpmap reg auto-gen
	-- /Game\Blueprints start
	BP_Als_Player = BpType.BP_Als_Player ,
	BP_Als_PlayerController = BpType.BP_Als_PlayerController ,
	BP_PlayerController = BpType.BP_PlayerController ,
	BP_PlayerState = BpType.BP_PlayerState ,
	BP_GameOwner = BpType.BP_GameOwner ,
	BP_LuaManager = BpType.BP_LuaManager ,
	BP_MessageManager = BpType.BP_MessageManager ,
	UI_EditorAnimRetarget = BpType.UI_EditorAnimRetarget ,
	UI_FoldPanel = BpType.UI_FoldPanel ,
	UI_SourceComboBox = BpType.UI_SourceComboBox ,
	-- /Game\Blueprints end

	-- /Game\UI start
	UI_BuildingWin = BpType.UI_BuildingWin ,
	UI_ItemBag = BpType.UI_ItemBag ,
	UI_LoadingWin = BpType.UI_LoadingWin ,
	UI_LoginWin = BpType.UI_LoginWin ,
	UI_MainWin = BpType.UI_MainWin ,
	UI_BuildingClassEntry = BpType.UI_BuildingClassEntry ,
	UI_BuildingItemEntry = BpType.UI_BuildingItemEntry ,
	UI_FunBtnEntry = BpType.UI_FunBtnEntry ,
	UI_PublicFunBtnEntry = BpType.UI_PublicFunBtnEntry ,
	UI_ItemGrid = BpType.UI_ItemGrid ,
	UI_BuildingBtn = BpType.UI_BuildingBtn ,
	UI_BagParent = BpType.UI_BagParent ,
	UI_MainParent = BpType.UI_MainParent ,
	-- /Game\UI end

	-- /Game\TouchSystem\Blueprints start
	UI_Camera = BpType.UI_Camera ,
	UI_Joystick = BpType.UI_Joystick ,
	UI_TouchWindow = BpType.UI_TouchWindow ,
	-- /Game\TouchSystem\Blueprints end

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
					GeneratedBpClassMap[k] = LoadClass(BpClassMap[k])
				elseif BpType[k] then 
					GeneratedBpClassMap[k] = LoadClass(BpType[k])
				end 
			end
			return GeneratedBpClassMap[k]
		end
	}
	self.BpClass = setmetatable({}, mt)
end
GA:loadBpClass()
