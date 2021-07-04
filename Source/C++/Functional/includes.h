

#pragma once

#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "winmm.lib")


#pragma warning(disable: 26812)
#pragma warning(disable: 26451)
#pragma warning(disable: 26495)
#pragma warning(disable: 4003)
#pragma warning(disable: 4715)

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
#include <iterator>
#include <fstream>
#include <sstream>
#include <type_traits>
#include <array>
#include <functional>
#include <string_view>

#define l(x) std::cout << x << "\n"

#define byte(x) sizeof(x)

#define Error(x) MessageBoxA(NULL,x,"Error", MB_ICONERROR);\
exit(-1)

#define Color(r,g,b) (DWORD)(((((255)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff))) // From DirectX

#define assert(con,rt) if(con)\
return rt

#define eassert(con,mes) if(con){ Error(mes);}

#define cpar(x) {x;}

//There are no errors in the code but the optimization could make some problems. Just use this if you are in Release mode.
#define _OPTIMIZATION_PROTECTION if(other->id == 0 || other->GetName() == "invalid") return;


#define _milliseconds(x) x
#define _seconds(x) x * 1000
#define _minutes(x) x * 60000

#define PREFAB
#define GAMEOBJECT
#define SINGLE

using namespace std::this_thread;
using namespace std::chrono;





#include "../Classes/Datatypes.h"
#include "CrossKnown.h"
#include "../Classes/Array.h"
#include "../Classes/Classes.h"
#include "../Classes/3D_Objects.h"
#include "../Lua/SurLua.h"
#include "../Classes/Audio.h"
//#include "functional.h" <- included in main so I don't get linker errors

constexpr i32 RO = 0;	//currently useless
constexpr i32 CO = 0;	//currently useless

extern sur::Vec2 _window_size;
extern sur::Vec2 _aspect;
extern HWND _hwnd;
extern HWND _consolehwnd;
extern sur::Maps _map;
extern bool _debug;
extern std::string _resource_path;
extern std::string _sound_path;