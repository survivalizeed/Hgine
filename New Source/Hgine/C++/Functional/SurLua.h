

#pragma once

#include <iostream>
#include <vector>
#include <Windows.h>
#include <string>
#include <string_view>

extern "C"
{
#include "../../Extern/Includes/Lua/lua.h"
#include "../../Extern/Includes/Lua/lauxlib.h"
#include "../../Extern/Includes/Lua/lualib.h"
}

#if _WIN32 || _WIN64
#if _WIN64
#pragma comment(lib, "F:\\C++\\Hgine\\Hgine\\Source\\Extern\\x64\\Lua\\liblua54.a")
#else
#pragma comment(lib, "F:\\C++\\Hgine\\Hgine\\Source\\Extern\\x86\\Lua\\liblua54.a")
#endif
#endif