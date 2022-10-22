local class = class(GA.Core,"Value")

function class:ctor(initialValue)
    self.currentValue = initialValue
    self.lastValue = initialValue
    self.callbacks = GA.Core.Event.new()
end

function class:set(newValue)
    if newValue ~= nil and self.currentValue ~= newValue then
        self.lastValue = self.currentValue
        self.currentValue = newValue
        self.callbacks:call(self.currentValue , self.lastValue)
    end
end

function class:get()
    return self.currentValue
end

function class:addChangeListener(obj, callback)
    self.callbacks:addListener(obj, callback)
end

function class:removeChangeListener(obj, callback)
    self.callbacks:removeListener(obj, callback)
end

return class