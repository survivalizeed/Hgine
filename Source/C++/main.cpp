

#include "Functional/includes.h"
#include "Lua/SurLua.h"

extern void Window(const char* name,int params);
extern sur::Map_Analyses _Amap;
extern sur::Input _input;

using sur::Instancer::Types;


int main() {
	lua_State* L = lua::LoadFile("F:\\C++\\Engine\\Engine\\Source\\Lua\\config.lua");
	_debug = stoi(lua::GetTableContent(L,"configuration","debug_mode"));
	_window_size(750, 750);
	_map = sur::Initialize();
	_Amap(_map, _window_size);
	
	Window(lua::GetTableContent(L, "configuration", "application_name").c_str(), WS_BORDER | WS_SYSMENU | WS_CAPTION);
	
	sur::Render renderer(Color(100, 107, 47));
	renderer.FPS();
	renderer.DebugConsole(_debug);
	int varx = 97;
	int vary = 56;
	sur::Triangle a({ 56,302 }, { 45,476 }, { 431,300 }, Color(123, 123, 123), "Cool", 12);
	for (;;) {
		renderer.ClearScreenBuffer();
		a.Bind(false);
		a.SetPosition(1, { varx, vary });
		renderer.RenderScreenBuffer();
	}
}

