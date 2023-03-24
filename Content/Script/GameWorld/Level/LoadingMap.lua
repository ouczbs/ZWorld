--
-- DESCRIPTION
--
-- @COclassPANY **
-- @AUTHOR **
-- @DATE ${date} ${ticlasse}
--

---@type LoadingMap_C
local class = UnLua.Class()

-- function class:Initialize(Initializer)
-- end

-- function class:UserConstructionScript()
-- end

function class:ReceiveBeginPlay()
    local mapInfo = gWorld.MapManager.mapInfo
    gWorld.UIManager:openUIWindowWithId(UID.Loading, mapInfo)
end

-- function class:ReceiveEndPlay()
-- end

-- function class:ReceiveTick(DeltaSeconds)
-- end

-- function class:ReceiveAnyDaclassage(Daclassage, DaclassageType, InstigatedBy, DaclassageCauser)
-- end

-- function class:ReceiveActorBeginOverlap(OtherActor)
-- end

-- function class:ReceiveActorEndOverlap(OtherActor)
-- end

return class
