
local class = class(GA.Login, "Account")

function class:LoginAccountCmd()
    local msg = {
        account = self.account,
        password = self.password
    }
    pbc.up.LoginAccountCmd(msg , nil , self.LoginAccountCmdAck)
end

function class:LoginAccountCmdAck(msg,request)
    logE(msg , request ,"LoginAccountCmdAck")
end