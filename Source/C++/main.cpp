#include "Functional/includes.h"
#include "Functional/functional.h"
#include "Functional/TemporaryObjects.h"
#include "Lua/SurLua.h"

lua_State* Start();
extern void Window(const char* name, int params);
extern sur::Map_Analyses _Amap;
extern sur::Input _input;

using sur::Instancer::Types;


int main() {
	lua_State* LC = Start();
	sur::Render renderer(Color(50, 50, 50), true,0);
	renderer.DebugConsole(_debug);
	renderer.FPS();

	i32 angle = 0;

	i64 snap = sur::GetMilliseconds();

	sur::Cuboid cuboid({ 200,200,200 }, { 300,200,200 }, { 300,300,200 }, { 200,300,200 },
		{ 200,200,300 }, { 300,200,300 }, { 300,300,300 }, { 200,300,300 }, Color(255, 0, 0), { 250,250,250 });
	
	sur::Cuboid cuboid2({ 100,100,100 }, { 200,100,100 }, { 200,200,100 }, { 100,200,100 },
		{ 100,100,200 }, { 200,100,200 }, { 200,200,200 }, { 100,200,200 }, Color(0, 255, 0), { 150,150,150 });

	for (;;) {
		renderer.ClearScreenBuffer();
		cuboid.Bind(true, 160);
		cuboid.Rotate(Dimension::Z, angle);
		cuboid.Rotate(Dimension::X, angle);
		cuboid.Rotate(Dimension::Y, angle);

		cuboid2.Bind(true, 160);
		cuboid2.Rotate(Dimension::Z, angle);
		cuboid2.Rotate(Dimension::X, angle);
		cuboid2.Rotate(Dimension::Y, angle);

		if (sur::GetMilliseconds() - snap >= _milliseconds(10)) {
			angle += 1;
			snap = sur::GetMilliseconds();
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