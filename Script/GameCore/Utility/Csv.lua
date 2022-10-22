
local Csv = {}
GA.Utility.Csv = Csv
function Csv.split(str,reps)
    local resultStrList = {}
    string.gsub(str,'[^'..reps..']+',function ( w )
        table.insert(resultStrList,w)
    end)
    return resultStrList
end
function Csv.loadCell(cell , type)
    if type == "number" then
        return tonumber(cell == "" and "0" or cell)
    elseif type == "json" then 
        return json.decode(cell)
    end
    return cell
end
--用于获取csv表
function Csv.loadFile(filePath) 
    -- 读取文件
    local file = io.open(filePath, "r")
    local data = file:read()
    -- 按行划分
    local lineStr = Csv.split(data, '\n\r')

    --[[
        第一行是字段,第二行是类型,第三行是描述
    ]]
    local titles = string.split(lineStr[1], ",")
    local types = string.split(lineStr[2], ",")
    local arrs = {}
    for i = 4, #lineStr, 1 do
        -- 一行中,每一列的内容
        local content = string.split(lineStr[i], ",")
        -- 以标题作为索引,保存每一列的内容,取值的时候这样取&#xff1a;arrs[1].Title
        local ID = Csv.loadCell(content[0] , types[0])
        arrs[ID] = {};
        for j = 2, #titles, 1 do
            arrs[ID][titles[j]] = Csv.loadCell(content[j] , types[j])
        end
    end
    return arrs
end