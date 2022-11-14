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
}
local Gui = {
    item_map = item_map,
    ID = ID
}

function Gui:getItemList()
    return item_map
end

GA.Config.Gui = Gui