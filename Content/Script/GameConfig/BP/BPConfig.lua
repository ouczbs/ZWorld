local item_list = {
    {bp_name = "BP_MMOGameMode" , lua_name = "MMOGameMode"},
    {bp_name = "UI_FunBtnEntry" , lua_name = "GameWorld.UI.Entry.FunBtnEntry"},
}
local BP = {
    item_list = item_list
}

function BP:getItemList()
    return item_list
end

GA.Config.BP = BP

