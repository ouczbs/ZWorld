#include "CppBindingLibs.h"
#include "System/MessageManager.h"
namespace proto
{
	int _send(lua_State* L)
	{
		size_t len = 0;
		const char* c = luaL_checklstring(L, 1, &len);
		int id = luaL_checkinteger(L, 2);
		std::string msg(c, len);

		if (AMessageManager::CheckValid()) {
			AMessageManager::I()->SendMessage(msg ,id );
		}
		return 1;
	}
}
namespace custom_log
{
	

}
