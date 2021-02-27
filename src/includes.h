

#pragma once

#pragma comment(lib,"F:\\C++\\###Includes###\\Lua x86\\liblua54.a")  //Be aware of x64 and x86 -> dll aswell!!!
#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "winmm.lib")


#pragma warning(disable: 26812)
#pragma warning(disable: 26451)
#pragma warning(disable: 26495)

#include <Windows.h>
#include <gdiplus.h>
#include <iostream>
#include <vector>
#include <thread>
#include <cstdlib>
#include <chrono>
#include <string>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <sstream>


//Link to the include folder
extern "C"
{
#include "lua.h"
#include "lauxlib.h"
#include "lualib.h"
}

//Call
#define _LUA_CALL_
#define _LUA_FUNC_(name) int _LUA_CALL_ name(lua_State* L){
#define _LUA_END_(ret) return ret;}


#define l(x) std::cout << x << "\n"
#define byte(x) sizeof(x)
#define Error(x) MessageBoxA(NULL,x,"Error", MB_ICONERROR);\
exit(-1)
#define Color(r,g,b) RGB(r,g,b)


using namespace std::this_thread;
using namespace std::chrono;


#include "Datatypes.h"
#include "Array.h"
#include "functional.h"
#include "Classes.h"


extern sur::Vec2 _window_size;
extern HWND _hwnd;
extern sur::Maps _map;
extern bool Debug;
