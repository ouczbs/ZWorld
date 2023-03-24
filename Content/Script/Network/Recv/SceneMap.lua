local class = GA.Network.ProtoDown

--修复物体存档更新
function class.UpdateRepairObjState(msg)
	ulog(LOG_TJH, "Balous >>> UpdateRepairObjState msg = " .. table.tostring(msg))
	gWorld.repairSystemManager:updateRepairObjState(msg)
end

--------------------------------------------------------------------------------
-- 地图数据，生成场景角色
--------------------------------------------------------------------------------
function class.AddMapEntry(msg)
	-- ulog(LOG_TJH, "Balous >>> AddMapEntry, msg = " .. table.tostring(msg))
	local stage = gWorld.stageManager:getGamePlayStage()
	if stage ~= nil then	
		stage.networkHandler:handleAddMapEntry(msg)
	end
end

function class.MapUserInfoCmd(msg)
    gWorld.MapManager:MapUserInfoCmd(msg)
end

function RequestMap(id)
    pbc.up.RequestMapCmd({id = id} ,self.RequestMapAck )
end

function RequestMapAck(request , msg)
    -- body
end