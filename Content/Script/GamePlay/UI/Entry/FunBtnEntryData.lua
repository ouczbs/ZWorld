local class = class(GA.UI, "FunBtnEntryData")

function class:ctor(id , data)
   self.id = id 
   self.data = data
end
function class:getText()
    return self.data.text
end
function class:getIconAssert()
    return LoadObject(self.data.icon)
   self.icon = data.icon
end