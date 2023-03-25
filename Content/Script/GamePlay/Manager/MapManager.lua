local class = class(GA.Manager, "MapManager")

function class:ctor()

end
local LoadingMap = "LoadingMap"
local EMapState = {
    None = 1,
    Loading = 2,
    Finish = 3,
}
class.EMapState = EMapState
function class:init()
    self.mapInfo = nil
    self.mapId = nil
    self.mapState = EMapState.None
end
function class:updateMapState(state)
    if state then 
        self.mapState = state 
        return
    end
    if self.mapState == EMapState.None then 
        return 
    elseif self.mapState == EMapState.Loading then 
        return
    elseif self.mapState == EMapState.Finish then 
        self.mapState = EMapState.None
        self:onChangeMapFinished()
    end
end
function class:onChangeMapFinished()
    local uiop = self.mapInfo.uiop
    local item = GA.Game.UIOperation[uiop]
    if not item then return end
    for _,v in ipairs(item.popid) do 
        gWorld.UIManager:openUIWindowWithId(v)
    end
end
function class:MapUserInfoCmd(msg)
    if self.mapId == msg.id then
        return
    end
    local mapInfo = GA.Game.MapInfo[msg.id]
    self.mapId = msg.id
    self.mapInfo = mapInfo
    self.mapState = EMapState.Loading
    UE.UGameplayStatics.OpenLevel(gWorld:getWorldObject(),LoadingMap , true)
end
GA:AddInitManager(class.__cname, class)
