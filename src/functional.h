

#pragma once

#include "includes.h"


namespace sur {
	sur::Maps Initialize();

	int CharCounter(char Char, std::string Data);

	void Sound(const char* path, unsigned int params);

	int RandomRange(int min, int max);
}

//namespace lua {
//	lua_State* LuaLoadFile(const std::string Data);
//
//	auto LuaGetBasicTable(lua_State* L, const char* name, const std::vector<std::string>& list);
//
//	std::string LuaCallFunction(lua_State* L, const char* Name, const std::vector<std::string>& params = { "" });
//
//	std::string LuaCallTableFunction(lua_State* L, const char* TName, const char* FName, const std::vector<std::string> params = { "" });
//
//	std::string LuaGetTableContent(lua_State* L, const char* TName, const char* Name);
//
//	std::string LuaGetContent(lua_State* L, const char* Name);
//}