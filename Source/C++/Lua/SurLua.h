

#pragma once

#include <iostream>
#include <vector>
#include <Windows.h>
#include <string>
#include <string_view>
//Link to the include folder
extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}


#if _WIN32 || _WIN64
#if _WIN64
#pragma comment(lib,"F:\\C++\\###Includes###\\Lua x64\\liblua54.a")  //Be aware of x64 and x86 -> dll aswell
#else
#pragma comment(lib,"F:\\C++\\###Includes###\\Lua x86\\liblua54.a")  //Be aware of x64 and x86 -> dll aswell
#endif
#endif


#define Error(x) MessageBoxA(NULL,x,"Error", MB_ICONERROR);\
exit(-1)

//Call
#define _LUA_CALL_
#define _LUA_FUNC_(name) int _LUA_CALL_ name(lua_State* L){
#define _LUA_END_(ret) return ret;}


namespace lua {

	inline lua_State* LoadFile(const std::string& Data) {
		lua_State* L = luaL_newstate();
		luaL_openlibs(L);
		if (luaL_dofile(L, Data.c_str()) != LUA_OK) {
			Error(lua_tostring(L, -1));
		}
		return L;
	}
	inline auto GetBasicTable(lua_State* L, const char* name, const std::vector<std::string>& list) {
		std::vector<std::string> vec;
		enum class type {
			number, string
		};
		auto typecheck = [](const std::string& var) -> type
		{
			try {
				stoi(var);
				return type::number;
			}
			catch (std::exception e) {
				return type::string;
			}
		};
		lua_getglobal(L, name);
		if (lua_istable(L, -1)) {
			for (int i = 0; i < list.size(); i++) {
				if (typecheck(list.at(i)) == type::number) {
					lua_pushnumber(L, stoi(list.at(i)));
					lua_gettable(L, -2);
					vec.push_back(lua_tostring(L, -1));
					lua_pop(L, 1);
				}
				else if (typecheck(list.at(i)) == type::string) {
					lua_pushstring(L, list.at(i).c_str());
					lua_gettable(L, -2);
					vec.push_back(lua_tostring(L, -1));
					lua_pop(L, 1);
				}
			}
		}
		return vec;
	}

	inline std::string CallFunction(lua_State* L, const char* Name, const std::vector<std::string>& params = { "" }) {
		lua_getglobal(L, Name);
		if (lua_isfunction(L, -1)) {
			for (auto val : params)
				lua_pushstring(L, val.c_str());
			lua_pcall(L, (int)params.size(), 1, 0);
			return lua_tostring(L, -1);
		}
		return "nil";
	}

	inline std::string LuaCallFunctionVoid(lua_State* L, const char* Name) {
		lua_getglobal(L, Name);
		if (lua_isfunction(L, -1)) {
			lua_pcall(L, 0, 1, 0);
			return lua_tostring(L, -1);
		}
	}

	inline void LuaCallVoidFunctionVoid(lua_State* L, const char* Name) {
		lua_getglobal(L, Name);
		if (lua_isfunction(L, -1)) {
			lua_pcall(L, 0, 0, 0);
		}
	}

	inline std::string CallTableFunction(lua_State* L, const char* TName, const char* FName, const std::vector<std::string> params = { "" }) {
		lua_getglobal(L, TName);
		if (lua_istable(L, -1)) {
			lua_pushstring(L, FName);
			lua_gettable(L, -2);
			if (lua_isfunction(L, -1)) {
				for (auto val : params)
					lua_pushstring(L, val.c_str());
				lua_pcall(L, (int)params.size(), 1, 0);
				return lua_tostring(L, -1);
			}
		}
		return "nil";
	}

	inline std::string GetTableContent(lua_State* L, const char* TName, const char* Name) {
		lua_getglobal(L, TName);
		if (lua_istable(L, -1)) {
			lua_pushstring(L, Name);
			lua_gettable(L, -2);
			if (lua_isstring(L, -1) || lua_isnumber(L, -1) || lua_isboolean(L, -1)) {
				return lua_tostring(L, -1);
			}
		}
		return "nil";
	}

	inline std::string GetContent(lua_State* L, const char* Name) {
		lua_getglobal(L, Name);
		if (lua_isstring(L, -1) || lua_isnumber(L, -1) || lua_isboolean(L, -1)) {
			return lua_tostring(L, -1);
		}
		return "nil";
	}
}