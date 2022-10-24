local class = class(GA.UI, "UIWindowBP")

function class:ctor(uobject)
    self.Object = uobject
end


function class:init(data)
    self.__uid = data.id
end

function class:destroy()
    self.Object:RemoveFromParent()
end

function class:show()
    self.Object:SetVisibility(UE.ESlateVisibility.Visible)
end

function class:hide()
    self.Object:SetVisibility(UE.ESlateVisibility.Collapsed)
end

function class:tick()

end