

#pragma once

#pragma comment(lib, "gdiplus.lib")
#pragma comment(lib, "winmm.lib")


#pragma warning(disable: 26812)
#pragma warning(disable: 26451)
#pragma warning(disable: 26495)
#pragma warning(disable: 4003)
#pragma warning(disable: 4715)
#pragma warning(disable: 4018)
#pragma warning(disable: 4552)


#include <Windows.h>
#include <gdiplus.h>
#include <iostream>
#include <vector>
#include <thread>
#include <cstdlib>
#include <chrono>
#include <string>
#include <math.h>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <sstream>
#include <array>
#include <functional>
#include <string_view>
#include <map>
#include <optional>

#define log(x) std::cout << x << "\n";

#define Error(x) MessageBoxA(NULL, x,"Error", MB_ICONERROR);\
DebugBreak()

#define Reminder(x) MessageBoxA(NULL, x, "Reminder", MB_ICONINFORMATION)

#define Color(r,g,b) (DWORD)(((((255)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))

#define _milliseconds(x) x
#define _seconds(x) x * 1000
#define _minutes(x) x * 60000

#define PREFAB
#define GAMEOBJECT
#define SINGLE

#undef min
#undef max

using namespace std::this_thread;
using namespace std::chrono;


extern "C"
{
#include "Extern/Includes/Lua/lua.h"
#include "Extern/Includes/Lua/lauxlib.h"
#include "Extern/Includes/Lua/lualib.h"
}

#include "C++/Classes/LuaScript/LuaScript.h"
#include "C++/Classes/Audio/Audio.h"
#include "C++/Classes/Math/Datatypes.h"
#include "C++/Classes/Math/Vectors.h"
#include "C++/Classes/Math/Matrices.h"
#include "C++/Classes/2D/Algorithms/AABB.h"
#include "C++/Functional/Globals/Linkage.h"
#include "C++/Functional/Misc/Window_Creation.h"
#include "C++/Functional/Misc/CrossKnown.h"
#include "C++/Classes/Input/Input.h"
#include "C++/Functional/Functions/Functions.h"
#include "C++/Classes/Renderer/Renderer.h"
#include "C++/Classes/2D/Algorithms/Line.h"
#include "C++/Classes/2D/Algorithms/Triangle.h"
#include "C++/Classes/2D/Algorithms/Form.h"
#include "C++/Classes/2D/Classes/Objects.h"
#include "C++/Classes/IniReader/IniReader.h"
#include "C++/Classes/3D/Mesh/Mesh.h"
#include "C++/Classes/3D/ParticleSystem3D/ParticleSystem3D.h"
#include "C++/Classes/Manager/Manager.h"


