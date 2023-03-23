local EFunBtnType = GA.Core.InscSequence.Generator(1)
local EFunBtnID = GA.Core.InscSequence.Generator(1)
-- 主界面功能按钮
local UID = GA.Config.Gui.ID
local item_list = {
    [EFunBtnID.ShopBtn] = {
        type = EFunBtnType.ActivityMain,
        text = "商城",
        icon = '/Game/TouchSystem/Textures/UI/ButtonCraft',
        uid = UID.ItemBag
    },
    [EFunBtnID.BossBtn] = {
        type = EFunBtnType.ActivityMain,
        text = "背包",
        icon = '/Game/TouchSystem/Textures/UI/ButtonDemolish',
        uid = UID.ItemBag
    },
    [EFunBtnID.QuestBtn] = {
        type = EFunBtnType.ActivityMain,
        text = "副本",
        icon = '/Game/TouchSystem/Textures/UI/ButtonBag',
        uid = UID.ItemBag
    },
    [EFunBtnID.PetBtn] = {
        type = EFunBtnType.ActivityMain,
        text = "暗器",
        icon = '/Game/TouchSystem/Textures/UI/ButtonCraft',
        uid = UID.ItemBag
    },
    [EFunBtnID.EquipBtn] = {
        type = EFunBtnType.ActivityMain,
        text = "寻宝",
        icon = '/Game/TouchSystem/Textures/UI/ButtonDemolish',
        uid = UID.ItemBag
    },
    [EFunBtnID.GuildBtn] = {
        type = EFunBtnType.ActivityMain,
        text = "符文",
        icon = '/Game/TouchSystem/Textures/UI/ButtonBag',
        uid = UID.ItemBag
    },
    [EFunBtnID.RuneBtn] = {
        type = EFunBtnType.ActivityMain,
        text = "日常",
        icon = '/Game/TouchSystem/Textures/UI/ButtonCraft',
        uid = UID.ItemBag
    },
    [EFunBtnID.DailyNeedTo] = {
        type = EFunBtnType.ActivityMain,
        text = "领主",
        icon = '/Game/TouchSystem/Textures/UI/ButtonDemolish',
        uid = UID.ItemBag
    },
    [EFunBtnID.PvpBtn] = {
        type = EFunBtnType.ActivityMain,
        text = "转职",
        icon = '/Game/TouchSystem/Textures/UI/ButtonBag',
        uid = UID.ItemBag
    },
    [EFunBtnID.MergeBtn] = {
        type = EFunBtnType.ActivityMain,
        text = "变强",
        icon = '/Game/TouchSystem/Textures/UI/ButtonBag',
        uid = UID.ItemBag
    }
}
local FunBtn = {}
function FunBtn:initItemList()

end
function FunBtn:toEntryData()
    local dataList = {}
    local _UICheck = GA.Config.UICheck
    local dclass = GA.UI.FunBtnEntryData
    for k, v in pairs(item_list) do
        if _UICheck(v.uid) then
            local data = dclass.new(k, v)
            table.insert(dataList, data)
        end
    end
    return dataList
end
function FunBtn:getItemList()
    return item_list
end
FunBtn:initItemList()
GA.Config.FunBtn = FunBtn
