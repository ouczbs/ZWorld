local item_list = {"a1","a2","a3","a4","a5","a6","a7"}
local item_map = {
    {bp_name = "asll1" , lua_name = "dsad22"},
    {bp_name = "asll2" , lua_name = "dsad23"},
    {bp_name = "asll3" , lua_name = "dsad24"},
    {bp_name = "asll4" , lua_name = "dsad25"},
    {bp_name = "asll5" , lua_name = "dsad26"},
    {bp_name = "asll6" , lua_name = "dsad27"},
}
local Test = {
    a = 1,
    b = {
       "?????sdasfsdf" , 
         "?????sdasfsdf" , 
        "?????sdasfsdf" , 
        "?????sdasfsdf" , 
        "?????sdasfsdf" , 
    },
    c = "xintaibengle",
    d = item_map
}

function Test:getItemList()
    return item_map
end

GA.Config.Test = Test

