

#pragma once

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
#include <type_traits>

#define l(x) std::cout << x << "\n"
#define byte(x) sizeof(x)
#define Error(x) MessageBoxA(NULL,x,"Error", MB_ICONERROR);\
exit(-1)
#define Color(r,g,b) RGB(r,g,b)
#define assert(con,rt) if(con)\
return rt


using namespace std::this_thread;
using namespace std::chrono;


#include "../Classes/Datatypes.h"
#include "../Classes/Array.h"
#include "../Classes/Classes.h"
//#include "functional.h" <- included in main so I don't get linker errors

constexpr i32 RO = 0;
constexpr i32 CO = 0;


extern sur::Vec2 _window_size;
extern HWND _hwnd;
extern HWND _consolehwnd;
extern sur::Maps _map;
extern bool _debug;
extern std::string _resource_path;
extern std::string _sound_path;