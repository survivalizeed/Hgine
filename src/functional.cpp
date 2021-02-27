

#include "functional.h"



extern sur::Map_Analyses _Amap;
extern sur::Vec2 _window_size;

sur::Maps sur::Initialize()
{
	if (_window_size.x == 0 || _window_size.y == 0) {
		Error("_window_size not initialized");
	}
	return { new int[_window_size.x * _window_size.y],new int[_window_size.x * _window_size.y], 
	new DWORD[_window_size.x * _window_size.y] };
}

int sur::CharCounter(char Char, std::string Data) {
	int counter = 0;
	for (int i = 0; i < Data.size(); i++) {
		if (Data[i] == Char) {
			counter++;
		}
	}
	return counter;
}

void sur::Sound(const char* path, unsigned int params)
{
	PlaySoundA(path, NULL, params);
}


//lua_State* lua::LuaLoadFile(const std::string Data) {
//	lua_State* L = luaL_newstate();
//	luaL_openlibs(L);
//	if (luaL_loadfile(L, Data.c_str()) != LUA_OK) 
//		Error(lua_tostring(L, -1));
//	return L;
//}
//
//auto lua::LuaGetBasicTable(lua_State* L, const char* name, const std::vector<std::string>& list) {
//	std::vector<std::string> vec;
//	enum class type {
//		number, string
//	};
//	auto typecheck = [](const std::string& var) -> type
//	{
//		try {
//			stoi(var);
//			return type::number;
//		}
//		catch (std::exception& e) {
//			return type::string;
//		}
//	};
//	lua_getglobal(L, name);
//	if (lua_istable(L, -1)) {
//		for (int i = 0; i < list.size(); i++) {
//			if (typecheck(list.at(i)) == type::number) {
//				lua_pushnumber(L, stoi(list.at(i)));
//				lua_gettable(L, -2);
//				vec.push_back(lua_tostring(L, -1));
//				lua_pop(L, 1);
//			}
//			else if (typecheck(list.at(i)) == type::string) {
//				lua_pushstring(L, list.at(i).c_str());
//				lua_gettable(L, -2);
//				vec.push_back(lua_tostring(L, -1));
//				lua_pop(L, 1);
//			}
//		}
//		return vec;
//	}
//}
//
//std::string lua::LuaCallFunction(lua_State* L, const char* Name, const std::vector<std::string>& params) {
//	lua_getglobal(L, Name);
//	if (lua_isfunction(L, -1)) {
//		for (auto val : params)
//			lua_pushstring(L, val.c_str());
//		lua_pcall(L, params.size(), 1, 0);
//		return lua_tostring(L, -1);
//	}
//	return "nil";
//}
//
//std::string lua::LuaCallTableFunction(lua_State* L, const char* TName, const char* FName, const std::vector<std::string> params) {
//	lua_getglobal(L, TName);
//	if (lua_istable(L, -1)) {
//		lua_pushstring(L, FName);
//		lua_gettable(L, -2);
//		if (lua_isfunction(L, -1)) {
//			for (auto val : params)
//				lua_pushstring(L, val.c_str());
//			lua_pcall(L, params.size(), 1, 0);
//			return lua_tostring(L, -1);
//		}
//		return "nil";
//	}
//}
//
//std::string lua::LuaGetTableContent(lua_State* L, const char* TName, const char* Name) {
//	lua_getglobal(L, TName);
//	if (lua_istable(L, -1)) {
//		lua_pushstring(L, Name);
//		lua_gettable(L, -2);
//		if (lua_isstring(L, -1) || lua_isnumber(L, -1) || lua_isboolean(L, -1)) {
//			return lua_tostring(L, -1);
//		}
//		return "nil";
//	}
//}
//
//std::string lua::LuaGetContent(lua_State* L, const char* Name) {
//	lua_getglobal(L, Name);
//	if (lua_isstring(L, -1) || lua_isnumber(L, -1) || lua_isboolean(L, -1)) {
//		return lua_tostring(L, -1);
//	}
//	return "nil";
//}