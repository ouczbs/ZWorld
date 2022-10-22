local sequence = GA.Core.InscSequence:new(1)
local Gui = {
    { id = sequence:insc(1) , name = "Login" , layout = GA.BpClass.UI_LoginWin , layar = GA.UI.Layers.Main }, 
    { id = sequence:insc() , name = "Main" , layout = GA.BpClass.UI_MainWin , layar = GA.UI.Layers.Main },
}
GA.Config.Gui = Gui