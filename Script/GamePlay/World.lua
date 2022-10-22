
require "GameCore.GC"
require "GamePlay.GP"
require "Network.Network_Module"

local class = class(GA,"World")

function class:ctor()  
    self._uWorldContext = nil
    self._registerManager = {}
end
function class:registerLuaManager(key , luaclass)  
    if self[key] then 
        return
    end
    local manager = luaclass.new()
    manager:init()
    self[key] = manager
    table.insert(self._registerManager , manager)
end
function class:InitializeGameWorld(GameMode)
    local WorldContext = GameMode:GetWorld()
    self.UGameMode = GameMode
    self._uWorldContext = WorldContext

    self.UGamePoolSubsystem = UE4.UGameOwnerLibrary.GetGameSubsystem(GA.BpClass.UGamePoolSubsystem)
    self.UGameTableSubsystem = UE4.UGameOwnerLibrary.GetGameSubsystem(GA.BpClass.UGameTableSubsystem)
    self.UGameOwnerSubsystem = UE4.UGameOwnerLibrary.GetGameSubsystem(GA.BpClass.UGameOwnerSubsystem)

    self.RequestTable = GA.Table.RequestTable.new("/Game/Table/RequestTable")
end
function class:InitializeLuaWorld()
    self:registerLuaManager("EventBus" , GA.Event.EventBus)
    self:registerLuaManager("InterfaceBus" , GA.Interface.InterfaceBus)
    self:registerLuaManager("InputManager" , GA.Input.InputManager)
    self:registerLuaManager("Scheduler" , GA.Time.Scheduler)
    self:registerLuaManager("UIManager" , GA.UI.UIManager)
    
    for key,luaclass in pairs(GA.initManagerList) do 
        self:registerLuaManager(key , luaclass)
    end
    GA.initManagerList = nil
    -- self.MessageManager:Connect(GameConfig.Host);
    -- local account = GA.Login.Account.new()
    -- account.account = "name"
    -- account.password = "psd"
    -- account:LoginAccountCmd()
    --self.MessageManager:SendMessage("sad");
end
function class:getWorldContext()
    return self._uWorldContext
end
function class:setWorld(world)
    self.world = world
end
function class:setGameWorld(GameWorld)
    self.GameWorld = GameWorld
end
function class:beginPlay()
    --local zero = UE4.FVector(0.0, 0.0, 0.0)
    --self.inputManage = GA.Manage.InputManage.new()

    -- local playerControl = UE4.UGameplayStatics.GetPlayerController(self.world, 0)
    -- self.playerNet = GA.Player.PlayerNet.new(playerControl)
    -- self.message_beginPlay:send()
end

function class:tick(dt)
    self.UGameOwnerSubsystem:Tick(dt)
    for _,manager in pairs(self._registerManager) do 
        if manager.tick then 
            manager:tick(dt)
        end
    end
end
function class:lateTick(dt)
    for _,manager in pairs(self._registerManager) do 
        if manager.lateTick then 
            manager:lateTick(dt)
        end
    end
end

function class:spawnActor(uclass, uLocation , uRotation , params)
    local transform = UE4.FTransform(uRotation:ToQuat(), uLocation)
    return self._uWorldContext:SpawnActor(uclass , transform , params and params.collisionHandle or UEnum.ESpawnActorCollisionHandlingMethod.AlwaysSpawn)
end

function class:spawnLuaActor(luaclass, uLocation , uRotation , params)
    local uclass,modulename = luaclass:GetUnluaBind()
    local transform = UE4.FTransform(uRotation:ToQuat(), uLocation)
    return self._uWorldContext:SpawnLuaActor(uclass , transform , params and params.collisionHandle or UEnum.ESpawnActorCollisionHandlingMethod.AlwaysSpawn , self , self, modulename)
end


return class