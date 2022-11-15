local ID = GA.Core.InscSequence.Generator(1)
local item_map = {
    Login = { 
        id = ID.Login,
        layout = GA.BpType.UI_LoginWin , 
        layer = GA.UI.Layers.Main ,
        script = "GameWorld.UI.Login.LoginWindow",
    }, 
    Main = { 
        id = ID.Main , 
        layout = GA.BpType.UI_MainWin ,
        layer = GA.UI.Layers.Main , 
        script = "GameWorld.UI.Main.MainWindow",
    },
    MainParent = { 
        id = ID.MainParent , 
        layout = GA.BpType.UI_MainParent ,
        layer = GA.UI.Layers.Parent, 
        script = "GameWorld.UI.Parent.MainParent",
    },
    ItemBag = { 
        id = ID.ItemBag , 
        layout = GA.BpType.UI_ItemBag ,
        layer = GA.UI.Layers.Tier1 , 
        script = "GameWorld.UI.Bag.ItemBagWindow",
        parent =  ID.MainParent, 
    },
    RelicBag = { 
        id = ID.RelicItemBag , 
        layout = GA.BpType.UI_RelicBag ,
        layer = GA.UI.Layers.Tier1 , 
        script = "GameWorld.UI.Bag.RelicBagWindow",
        parent =  ID.MainParent, 
    },
    EquipBag = { 
        id = ID.EquipBag , 
        layout = GA.BpType.UI_EquipBag ,
        layer = GA.UI.Layers.Tier1 , 
        script = "GameWorld.UI.Bag.EquipBagWindow",
        parent =  ID.MainParent, 
    },
    HomeBag = { 
        id = ID.HomeBag , 
        layout = GA.BpType.UI_HomeBag ,
        layer = GA.UI.Layers.Tier1 , 
        script = "GameWorld.UI.Bag.HomeBagWindow",
        parent =  ID.MainParent, 
    },
}
local Gui = {
    item_map = item_map,
    ID = ID
}
function Gui:initItemList()
    for k,v in pairs(item_map) do 
        v.name = k
    end
end
function Gui:getItemList()
    return item_map
end
function Gui:getItemByName(name)
    return item_map[name]
end
local _UIIdCacheList = {}
function Gui:getItemById(id)
    local item = _UIIdCacheList[id]
    if item then 
        return item
    end
    for k,v in pairs(item_map) do 
        if v.id == id then 
            _UIIdCacheList[id] = v
            return v
        end
    end
end
Gui:initItemList()
GA.Config.Gui = Gui