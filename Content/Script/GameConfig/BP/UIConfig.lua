local sequence = GA.Core.InscSequence.new(1)
local item_map = {
    Login = { 
        id = sequence:insc(1) ,
        layout = GA.BpType.UI_LoginWin , 
        layer = GA.UI.Layers.Main ,
        script = "GameWorld.UI.Login.LoginWindow",
    }, 
    Main = { 
        id = sequence:insc() , 
        layout = GA.BpType.UI_MainWin ,
        layer = GA.UI.Layers.Main , 
        script = "GameWorld.UI.Main.MainWindow",
    },
    BaseWindow = { 
        id = sequence:insc() , 
        layout = GA.BpType.UI_ItemBag ,
        layer = GA.UI.Layers.Tier1 , 
        script = "GameWorld.UI.Bag.ItemBagWindow",
    },
    ItemBag = { 
        id = sequence:insc() , 
        layout = GA.BpType.UI_BaseWindow ,
        layer = GA.UI.Layers.Tier1 , 
        script = "GameWorld.UI.Super.BaseWindow",
    },
}
local Gui = {
    item_map = item_map
}

function Gui:getItemList()
    return item_map
end

GA.Config.Gui = Gui