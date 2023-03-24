local WITH_LUAIDE_DEBUG = true
if WITH_LUAIDE_DEBUG then
    require "socket.core"
    require("LuaPanda").start("127.0.0.1", 8818)
end
require "GameGlobal"
require "GameCore.GC"
require "GameConfig.GC"
require "GamePlay.GP"
require "GameMaster.GM"
require "Network.Network_Module"

local class = class(GA, "World")

function class:ctor()
    self._uWorldContext = nil
    self._registerManager = {}
end
function class:registerLuaManager(key, luaclass)
    if self[key] then
        return
    end
    local manager = luaclass.new()
    manager:init()
    self[key] = manager
    table.insert(self._registerManager, manager)
end
function class:registerUManager(key, uclass, script)
    local manager = self:spawnLuaActor(uclass, script, UE.FVector(0.0, 0.0, 0.0), UE.FRotator(0, 0, 0))
    manager:init()
    self[key] = manager
    table.insert(self._registerManager, manager)
end
function class:CreateSubSystem()
    self.UGamePoolSubsystem = UE.UGameOwnerLibrary.GetGameSubsystem(UE.UGamePoolSubsystem)
end
function class:ReInitializeWorld(WorldContext)
    self._uWorldContext = WorldContext
end
function class:InitializeWorld(WorldContext)
    self:CreateSubSystem()
    self._uWorldContext = WorldContext

    self:registerLuaManager("EventBus", GA.Event.EventBus)
    self:registerLuaManager("InterfaceBus", GA.Interface.InterfaceBus)
    self:registerLuaManager("InputManager", GA.Input.InputManager)
    self:registerLuaManager("Scheduler", GA.Time.Scheduler)
    self:registerLuaManager("UIManager", GA.UI.UIManager)

    -- self:registerUManager("VoxelWorld", UE.AVoxelWorld, gLuaObject.AVoxelWorld)
    self:registerUManager("MessageManager", UE.AMessageManager, gLuaObject.AMessageManager)
    
    for key, luaclass in pairs(GA.initManagerList) do
        self:registerLuaManager(key, luaclass)
    end
    GA.initManagerList = nil
    self.MessageManager:Connect(gGameConst.Host);
    -- local account = GA.Login.Account.new()
    -- account.account = "name"
    -- account.password = "psd"
    -- account:LoginAccountCmd()
    -- self.MessageManager:SendMessage("sad");
    pbc.Send("hello message", 12)
end
function class:getWorldContext()
    return self._uWorldContext
end
function class:getWorldObject()
    return self._uWorldContext
end
function class:getMainController()
    return UE.UGameplayStatics.GetPlayerController(self._uWorldContext, 0)
end
function class:getMainPlayer()
    return UE.UGameplayStatics.GetPlayerPawn(self._uWorldContext, 0)
end
function class:beginPlay()
    pbc.down.MapUserInfoCmd({id = 1})
    -- local zero = UE.FVector(0.0, 0.0, 0.0)
    -- self.inputManage = GA.Manage.InputManage.new()

    local playerControl = UE.UGameplayStatics.GetPlayerController(self.world, 0)
    if playerControl then
        playerControl.bShowMouseCursor = true
    end
    -- self.playerNet = GA.Player.PlayerNet.new(playerControl)
    -- self.message_beginPlay:send()
end
function class:tick(dt)
    for _, manager in pairs(self._registerManager) do
        if manager.tick then
            manager:tick(dt)
        end
    end
end
function class:lateTick(dt)
    for _, manager in pairs(self._registerManager) do
        if manager.lateTick then
            manager:lateTick(dt)
        end
    end
end

function class:spawnActor(uclass, uLocation, uRotation, params)
    local transform = UE.FTransform(uRotation:ToQuat(), uLocation)
    return self._uWorldContext:SpawnActor(uclass, transform, params and params.collisionHandle or
        UE.ESpawnActorCollisionHandlingMethod.AlwaysSpawn)
end

function class:spawnLuaActor(uclass, script, uLocation, uRotation, params)
    local transform = UE.FTransform(uRotation:ToQuat(), uLocation)
    return self._uWorldContext:SpawnActor(uclass, transform, params and params.collisionHandle or
        UE.ESpawnActorCollisionHandlingMethod.AlwaysSpawn, self, self, script)
end

return class
