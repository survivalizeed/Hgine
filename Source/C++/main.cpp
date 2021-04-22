

#include "Functional/includes.h"
#include "Functional/functional.h"
#include "Lua/SurLua.h"

lua_State* Start();
extern void Window(const char* name, int params);
extern sur::Map_Analyses _Amap;
extern sur::Input _input;

using sur::Instancer::Types;


int main() {
	lua_State* LC = Start();

	sur::Render renderer(Color(0, 0, 0),true,1);
	renderer.DebugConsole(true);
	renderer.FPS();
	
	sur::Mat2x2 a(1, 0,		// A matrix you can play with ;)
				  0, 1);

	for (;;) {
		renderer.ClearScreenBuffer();
		for (i32 i = 0; i < 50; ++i) {
			for (i32 j = 0; j < 50; ++j) {
				_Amap.Render(a.mulitplyWithVector({ j, i }), Color(125, 125, 0));
			}
		}

		renderer.RenderScreenBuffer();
	}
}

lua_State* Start() {
	lua_State* L = lua::LoadFile("F:\\C++\\Hgine\\Hgine\\Source\\Lua\\config.lua");
	_debug = stoi(lua::GetTableContent(L, "configuration", "debug_mode"));

	_window_size(stoi(lua::GetTableContent(L, "configuration", "window_size_x")),
		stoi(lua::GetTableContent(L, "configuration", "window_size_y")));

	_resource_path = lua::GetTableContent(L, "configuration", "resource_path");

	_sound_path = lua::GetTableContent(L, "configuration", "sound_path");

	_map = sur::Initialize();

	_Amap(_map, _window_size);

	//Create the Window with some parameters
	Window(lua::GetTableContent(L, "configuration", "application_name").c_str(), WS_OVERLAPPEDWINDOW);

	return L;
}
