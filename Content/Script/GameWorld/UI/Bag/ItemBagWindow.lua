

---@type ItemBagWindow
local class = UnLua.Class(GA.UI.UIWindow)
GA.UI.ItemBagWindow = class
function class:Construct()
    logE(self.GridPanel, "ItemBagWindow")
    -- for i = 1,12 do 
    --     for j=1,12 do
    --         local layout = GA.BpClass.UI_ItemGrid
    --         local widget = NewObject(layout, gWorld:getWorldContext())
    --         self.GridPanel:AddChildToUniformGrid(widget,i , j)
    --         logE("hhahahh")
    --     end
    -- end
end

return class