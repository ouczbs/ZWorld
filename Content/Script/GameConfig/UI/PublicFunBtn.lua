local fun_list = {
    [1] = {name = "装备" , icon = "12"},
    [2] = {name = "背包" , icon = "12"},
    [3] = {name = "副本" , icon = "23"},
}
local class = class()

function class:toEntryData()
    if not GA.UI.FunBtnEntryData then 
        return fun_list
    end
    local data_list = {}
    for k,v in pairs(fun_list) do 
        data_list[k] = GA.UI.FunBtnEntryData.new(v)
    end
    return data_list
end
GA.UI.PublicFunBtn = class