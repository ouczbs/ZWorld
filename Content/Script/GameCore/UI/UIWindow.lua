local class = class(GA.UI, "UIWindow")

function class:ctor()

end

function class:init(data, state)
    self.__uid = data.id
    if self.onInit then 
        self:onInit(data, state)
    end
end

function class:destroy()
    self:RemoveFromParent()
    self:Release()
    if self.onDestroy then 
        self:onDestroy()
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