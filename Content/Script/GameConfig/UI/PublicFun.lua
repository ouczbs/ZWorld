local EPublicFunType = {
    Bag = 1,
    Role = 2,
}
-- 功能界面按钮组合
local UID = GA.Config.Gui.ID
local PublicFun = {
    [EPublicFunType.Bag] = {
        {
            uid = UID.ItemBag,
            text = "道具",
            icon = "",
            bg = "",
        },
        {
            uid = UID.EquipBag,
            text = "装备",
            icon = "",
            bg = "",
        },
        {
            uid = UID.RelicBag,
            text = "圣遗物",
            icon = "",
            bg = "",
        },
        {
            uid = UID.HomeBag,
            text = "家园",
            icon = "",
            bg = "",
        },
    },
    [EPublicFunType.Role] = {

    },
}
local _cacheUIType = {}
local function findUIListByID(uid)
    local type = _cacheUIType[uid]
    if type then 
        return PublicFun[type], type
    end
    for k1,v1 in ipairs(PublicFun) do 
        for _,v2 in ipairs(v1) do 
            if uid == v2.uid then 
                _cacheUIType[uid] = k1
                return PublicFun[k1], k1
            end
        end
    end
end
function PublicFun:getUIListByID(uid)
    local list,type = findUIListByID(uid)
    if not list then return end
    local _UICheck = GA.Config.UICheck
    local newList = {}
    for k,v in ipairs(list) do 
        if _UICheck(v.uid) then 
            table.insert(newList , v)
        end
    end
    return newList,type
end
GA.Config.PublicFun = PublicFun