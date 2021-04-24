

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
	
	sur::Object b(_resource_path + "bottle.hgineres", { 200, 200 }, "hallo", 12);

	sur::Rectangle r({ 0,0 }, { 100,100 }, Color(124, 52, 255), "R", 34, false);
	
	b.matrix(1,-1,
		     0, 1);

	for (;;) {
		renderer.ClearScreenBuffer();
		r.Bind(true, true);
		b.Bind(true, ColliderType::Outline);
		
		if (_input.keyboard.Key(Keys::A)) {
			r.Move({ -3,0 }, true);
		}
		if (_input.keyboard.Key(Keys::D)) {
			r.Move({ 3,0 }, true);
		}
		if (_input.keyboard.Key(Keys::W)) {
			r.Move({ 0,3 }, true);
		}
		if (_input.keyboard.Key(Keys::S)) {
			r.Move({ 0,-3 }, true);
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
