
#include "Functional/includes.h"
#include "Functional/functional.h"
#include "Lua/SurLua.h"

lua_State* Start();
extern void Window(const char* name, int params);
extern sur::Map_Analyses _Amap;
extern sur::Input _input;

using sur::Instancer::Types;

// The object id always needs to be different because otherwise it will call the 
// callback of the first object it finds -> include hash algorithm ?

int main() {
	lua_State* LC = Start();

	sur::Render renderer(Color(100, 107, 47), 1);
	renderer.DebugConsole(true);
	renderer.FPS();

	//sur::Object b(_resource_path + "Bottle.Hgineres", { 0,200 }, "obj", 1);
	sur::Rectangle a({ 100,100 }, { 30,30 }, Color(124, 124, 124), "a", 1);
	sur::Rectangle b({ 200,200 }, { 30,30 }, Color(124, 124, 124), "b", 2, [](sur::Master* current, sur::Master* other) {
		if (other->GetName() == "a")
			l("Collision");
	});

	sur::Vec2f dir(a.GetPosition() - b.GetPosition());
	dir.normalize();
	for (;;) {
		renderer.ClearScreenBuffer();
		a.Bind(true, true);
		b.Bind(true, true);
		b.Move(dir * 2, true);
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
