local class = class(GA.Table, "RequestTable")
local RequestTable = nil
function class:ctor(path)
    self.DataTable = LoadObject(path)
    self.StructRows = GA.Table.GetStructRows(self , self.InitLuaRows)
    self.LuaRows = {}
end
function class:SpawnRequest(name)
    local row = self.StructRows[name]
    local request = nil
    if row then
        local luarow = self.LuaRows[name]
        request = gWorld.UGamePoolSubsystem:Spawn(GA.BpClass[luarow.Class])
        self:InitRequestFromRow(request , name)
    end
    print("Spawn Request : " , request)
    return request
end
function class:InitLuaRows(row , name)
    local luarow = {}
    luarow.Class = UE4.UKismetSystemLibrary.Conv_SoftClassReferenceToString(row.Class)
    --luarow.ConditionTags = json.decode(row.ConditionTags)
    --luarow.ActiveTags = json.decode(row.ActiveTags)
    self.LuaRows[name] = luarow
end
function class:InitRequestFromRow(request, name)
    local row = self.StructRows[name]
    local luarow = self.LuaRows[name]
	request.IsOnly = row.IsOnly
    request.IsPersistence = row.IsPersistence
end