

#pragma once

#pragma comment(lib,"gdiplus.lib")


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
#include "LoadObj.h"


extern sur::Vec2 _window_size;
extern HWND _hwnd;
extern sur::Maps _map;

