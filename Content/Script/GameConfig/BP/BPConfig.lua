local item_map = {
    MMOGameMode = "MMOGameMode",
    UI_FunBtnEntry = "GameWorld.UI.Entry.FunBtnEntry",
}
local BP = {
    item_map = item_map
}

function BP:getItemList()
    return item_map
end

GA.Config.BP = BP