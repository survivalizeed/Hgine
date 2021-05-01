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

	sur::Vec3f origin(200, 200, 200);

	std::array<sur::Vec3f, 12> points;
	points[0] = { 150,150,150 };
	points[1] = { 250,150,150 };
	points[2] = { 250,250,150 };
	points[3] = { 150,250,150 };
	points[4] = { 150,150,150 };
	
	points[5] = { 150,150,250 };
	points[6] = { 250,150,250 };
	points[7] = { 250,250,250 };
	points[8] = { 150,250,250 };
	points[9] = { 150,150,250 };

	points[10] = { 150,250,250 };
	points[11] = { 150,250,150 };

	std::vector<sur::Vec3f> ps;
	for (;;) {
		renderer.ClearScreenBuffer();	
		
		for (auto&& iter : points) {			
			sur::Vec3f tmp(iter);
			tmp = sur::RotateX(tmp, origin, angle);
			tmp = sur::RotateY(tmp, origin, angle);
			tmp = sur::RotateZ(tmp, origin, angle);
			ps.push_back(tmp);
		}

		for (i32 i = 0; i < ps.size() - 1; ++i) {
			sur::TMP::Line(ps[i].toVec2(), ps[i + 1].toVec2(), Color(0, 255, 0));
		}
		ps.clear();

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
