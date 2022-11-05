local EFunBtnType = {
    ActivityMain = 1,
    ImportanceMenu = 2,
    MainMenu = 3,

}
local EFunBtnID = {
    ShopBtn =  1,
    BossBtn = 2,
    QuestBtn = 3,
    PetBtn = 4,
    EquipBtn = 5,
    GuildBtn = 6,
    RuneBtn = 7,
    DailyNeedTo = 8,
    PvpBtn = 9,
    MergeBtn = 10,
}
local item_list = {
    [EFunBtnID.ShopBtn] = { 
        type = EFunBtnType.ActivityMain,
        text = "商城",
        icon = '/Game/TouchSystem/Textures/UI/ButtonCraft'
    },
    [EFunBtnID.BossBtn] = { 
        type = EFunBtnType.ActivityMain,
        text = "背包",
        icon = '/Game/TouchSystem/Textures/UI/ButtonDemolish'
    },
    [EFunBtnID.QuestBtn] = { 
        type = EFunBtnType.ActivityMain,
        text = "副本",
        icon = '/Game/TouchSystem/Textures/UI/ButtonBag'
    },
    [EFunBtnID.PetBtn] = { 
        type = EFunBtnType.ActivityMain,
        text = "暗器",
        icon = '/Game/TouchSystem/Textures/UI/ButtonCraft'
    },
    [EFunBtnID.EquipBtn] = { 
        type = EFunBtnType.ActivityMain,
        text = "寻宝",
        icon = '/Game/TouchSystem/Textures/UI/ButtonDemolish'
    },
    [EFunBtnID.GuildBtn] = { 
        type = EFunBtnType.ActivityMain,
        text = "符文",
        icon = '/Game/TouchSystem/Textures/UI/ButtonBag'
    },
    [EFunBtnID.RuneBtn] = { 
        type = EFunBtnType.ActivityMain,
        text = "日常",
        icon = '/Game/TouchSystem/Textures/UI/ButtonCraft'
    },
    [EFunBtnID.DailyNeedTo] = { 
        type = EFunBtnType.ActivityMain,
        text = "领主",
        icon = '/Game/TouchSystem/Textures/UI/ButtonDemolish'
    },
    [EFunBtnID.PvpBtn] = { 
        type = EFunBtnType.ActivityMain,
        text = "转职",
        icon = '/Game/TouchSystem/Textures/UI/ButtonBag'
    },
    [EFunBtnID.MergeBtn] = { 
        type = EFunBtnType.ActivityMain,
        text = "变强",
        icon = '/Game/TouchSystem/Textures/UI/ButtonBag'
    },
}
local FunBtn = {}
function FunBtn:initItemList()

end
function FunBtn:toEntryData()
    local dataList = {}
    local dclass = GA.UI.FunBtnEntryData
    for k,v in pairs(item_list) do 
        local data = dclass.new(k,v)
        table.insert(dataList , data)
    end
    return dataList
end
function FunBtn:getItemList()
    return item_list
end
FunBtn:initItemList()
GA.Config.FunBtn = FunBtn