

#include "LuaScript.h"

sur::LuaScript::LuaScript(std::string_view fileName)
{
	handle = luaL_newstate();
	if (luaL_dofile(handle, fileName.data()) != LUA_OK) {
		Error(lua_tostring(handle, -1));
	}
}

void sur::LuaScript::RegisterFunction(std::string_view name, int(*function)(lua_State*))
{
	lua_register(handle, name.data(), function);
}
