

#pragma once

#include "../../../Includes.h"
#if _WIN32 || _WIN64
#if _WIN64
#pragma comment(lib,"F:\\C++\\Hgine_remake\\Hgine_remake\\Source\\Hgine\\Extern\\x64\\Lua\\lua54.lib")
#else
#pragma comment(lib,"F:\\C++\\Hgine_remake\\Hgine_remake\\Source\\Hgine\\Extern\\x86\\Lua\\lua54.lib")
#endif
#endif

namespace sur
{
	enum class LuaDatatype
	{

		Int,
		Float,
		String,
		Void

	};

	class LuaScript
	{
	private:

		lua_State* handle;

	public:

		LuaScript(std::string_view fileName);

		template<LuaDatatype type>
		auto CallFunction(std::string_view name, const std::vector<std::string_view> parameters = {}) {
			lua_getglobal(handle, name.data());
			for (auto& val : parameters)
				lua_pushstring(handle, val.data());
			if (lua_pcall(handle, parameters.size(), 1, 0) != 0) {
				Error(lua_tostring(handle, -1));
			}
			std::string tmp = lua_tostring(handle, -1);
			if constexpr (type == LuaDatatype::Int)
				return stoi(tmp);
			if constexpr (type == LuaDatatype::Float)
				return stof(tmp);
			if constexpr (type == LuaDatatype::String)
				return tmp;
			if constexpr (type == LuaDatatype::Void)
				return;
		}

		void RegisterFunction(std::string_view name, int(*function)(lua_State*));

	};
}