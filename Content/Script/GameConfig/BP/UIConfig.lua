local ID = GA.Core.InscSequence.Generator(1)
local BpType = GA.BpType
local Layers = GA.UI.Layers
local item_list = {
    [ID.Login] = { 
        layout = BpType.UI_LoginWin , 
        layer = Layers.Main ,
        script = "GameWorld.UI.Login.LoginWindow",
    }, 
    [ID.Main] = { 
        layout = BpType.UI_MainWin ,
        layer = Layers.Main , 
        script = "GameWorld.UI.Main.MainWindow",
    },
    [ID.MainParent] = {  
        layout = BpType.UI_MainParent ,
        layer = Layers.Parent, 
        script = "GameWorld.UI.Parent.MainParent",
    },
    [ID.ItemBag] = { 
        layout = BpType.UI_ItemBag ,
        layer = Layers.Tier1 , 
        script = "GameWorld.UI.Bag.ItemBagWindow",
        parent =  ID.MainParent, 
    },
    [ID.RelicItemBag] = { 
        layout = BpType.UI_RelicBag ,
        layer = Layers.Tier1 , 
        script = "GameWorld.UI.Bag.RelicBagWindow",
        parent =  ID.MainParent, 
    },
    [ID.EquipBag] = { 
        layout = BpType.UI_EquipBag ,
        layer = Layers.Tier1 , 
        script = "GameWorld.UI.Bag.EquipBagWindow",
        parent =  ID.MainParent, 
    },
    [ID.HomeBag] = { 
        layout = BpType.UI_HomeBag ,
        layer = Layers.Tier1 , 
        script = "GameWorld.UI.Bag.HomeBagWindow",
        parent =  ID.MainParent, 
    },
}
local Gui = {
    item_list = item_list,
    ID = ID
}
function Gui:initItemList()
    for k,v in ipairs(item_list) do 
        v.id = k
    end
end
function Gui:getItemList()
    return item_list
end
function Gui:getItemById(id)
    return item_list[id]
end
Gui:initItemList()
GA.Config.Gui = Gui