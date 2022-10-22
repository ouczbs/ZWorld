GA.Table = {}
local GetDataTableRowFromName = nil
GA.Table.GetStructRows = function(self , InitLuaRows)
    GetDataTableRowFromName = GetDataTableRowFromName or UE4.UDataTableFunctionLibrary.GetTableDataRowFromName
    local struct = nil
    local mt = {
        __index = function(t, name)
            local struct = struct or self.DataTable.RowStruct()
            local bFoundRow = GetDataTableRowFromName(self.DataTable , name , struct)
            if not bFoundRow then 
                return false
            end
            local outStruct = struct
            struct = nil
            InitLuaRows(self , outStruct , name)
            return outStruct
        end
    }
    local cppTable = {}
    setmetatable(cppTable, mt)
    return cppTable
end
require "GamePlay.Table.RequestTable"