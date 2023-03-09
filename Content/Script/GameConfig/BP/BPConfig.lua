local item_list = {
    {bp_name = "BP_MMOGameMode" , lua_name = "MMOGameMode"},
    {bp_name = "BP_LuaManager" , lua_name = "GameWorld.Manager.LuaManager"},
    {bp_name = "BP_MessageManager" , lua_name = "GameWorld.Manager.MessageManager"},
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

