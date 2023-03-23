
local class = class(GA.Utility, "Promise")

function class.Then(callback, next , ...)
    next = next or self.next
    if next and callback then 
        self.next = nil
        callback(...)
    end
    return class
end