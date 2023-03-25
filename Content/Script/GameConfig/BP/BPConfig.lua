local item_list = {
    {bp_name = "UI_FunBtnEntry" , lua_name = "GameWorld.UI.Entry.FunBtnEntry"},
    {bp_name = "UI_PublicFunBtnEntry" , lua_name = "GameWorld.UI.Entry.PublicFunBtnEntry"},
    {bp_name = "UI_ItemGrid" , lua_name = "GameWorld.UI.Grid.ItemGrid"},
    {bp_name = "BP_Als_Player" , lua_name = "GameWorld.Character.AlsPlayer"},
    {bp_name = "BP_Als_PlayerController" , lua_name = "GameWorld.Character.AlsPlayerController"},
}
local BP = {
    item_list = item_list
}

function BP:getItemList()
    return item_list
end

GA.Config.BP = BP

