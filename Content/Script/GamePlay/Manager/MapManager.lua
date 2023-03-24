local class = class(GA.Manager, "MapManager")

function class:ctor()

end
local LoadingMap = "LoadingMap"
function class:init()
    self.mapInfo = nil
    self.mapId = nil
end
function class:MapUserInfoCmd(msg)
    if self.mapId == msg.id then
        return
    end
    local mapInfo = GA.Game.MapInfo[msg.id]
    local uiop = mapInfo.uiop
    self.mapId = msg.id
    self.mapInfo = mapInfo
    UE.UGameplayStatics.OpenLevel(gWorld:getWorldObject(),LoadingMap , true)
end
GA:AddInitManager(class.__cname, class)
