--
-- DESCRIPTION
--
-- @COMPANY **
-- @AUTHOR **
-- @DATE ${date} ${time}
--

---@type UI_LoadingWin_C
local class = UnLua.Class(GA.UI.UIWindow)
local Library = UE.UGABlueprintFunctionLibrary
function class:Construct()
    self.bHasScriptImplementedPaint = 1
end
function class:onDestroy()
    UE.UGameplayStatics.OpenLevel(gWorld:getWorldObject(), self.level, true)
end
function class:onInit(data, param)
    self.package = param.package
    self.level = param.level
    self.percent = 0
    self.isLoaded = nil
    Library.AsyncLoadPackage(self.package, function(_, IsSuccess)
        self.isLoaded = true
        self.isSuccess = IsSuccess
    end)
end

function class:OnPaint(_)
    local percent  = 1
    if not self.isLoaded then
        percent = Library.GetLoadProgress(self.package)
    end
    self.Bar:SetPercent(percent)
    if self.percent == 1 and percent == 1 then
        self:rqDestroy()
    end
    self.percent = percent
end

return class
