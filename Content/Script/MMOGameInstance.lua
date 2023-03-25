--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--
require "World"

---@type BP_MMOGameInstance_C
local class = UnLua.Class()
function class:OverrideInitGame()
    GA.CreateGlobalVar()
    pbc.EncodeConfig(GA.Config.Gui, "GuiConfig")
    pbc.EncodeConfig(GA.Config.BP, "BPConfig")
    -- GA.Config.TestBP = pbc.DecodeConfig("BPConfig")
    -- 创建各种message
    local WorldContext = self:GetWorld()
    gWorld:InitializeWorld(WorldContext)
end
function class:OverrideWorldChanged(_ , NewWorld)
    if gWorld then
        gWorld:ReInitializeWorld(NewWorld)
    end
end
function class:ReceiveBeginPlay()
    print("BP_MMOGameInstance_C ReceiveBeginPlay")
    if gWorld then
        gWorld:beginPlay()
    end
end
function class:ReceiveTick(dt)
    if gWorld then
        gWorld:tick(dt)
        gWorld:lateTick(dt)
    end
end

return class