--预定义层级，UIBase子类需要通过s_layer变量指定自身层级
GA.UI.Layers = {
    Widgets3D           = 1,        --血量条，任务图标，对话气泡（在BPUICommon设置了ZOrder，重构时记得写在Lua里）
    Main                = 2, 	    --主界面，menumain专用
    Parent              = 3, 	    --父界面，功能菜单专用
    Tier1 	            = 4, 	    --功能一级界面
    TeamInfoWindow      = 5,        --编队界面
    Dialog 	            = 6,        --对话界面
    Tier2 	            = 7,        --功能二级界面
    Msg                 = 8,        --弹出框
    Reserved            = 9,        --保留层
    CameraBlend         = 10,        --摄像机融合切换
    Loading             = 11,        --Loading层
    Top                 = 12,       --最上层
    Debug               = 13, 	    --Debug类界面专用
}