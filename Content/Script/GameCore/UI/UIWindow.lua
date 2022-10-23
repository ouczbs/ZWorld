local class = class(GA.UI, "UIWindow")

function class:ctor()

end

function class:init(data)
    self.__uid = data.id
    self.__cname = data.name
    if self.onInit then 
        self:onInit(data)
    end
end

function class:destroy(bClear)
    self:RemoveFromParent()
    logE(self.__cname .. " Destroy")
    if self.onDestroy then 
        self:onDestroy()
    end
    if not bClear then 
        gWorld.UIManager:RemoveFromParent
    end
end

function class:show()
    self:SetVisibility(UE.ESlateVisibility.Visible)
    if self.onShow then 
        self:onShow()
    end
end

function class:hide()
    self:SetVisibility(UE.ESlateVisibility.Collapsed)
    if self.onHide then 
        self:onHide()
    end
end

function class:tick()
    if self.onInit then 
        self:onInit()
    end
end