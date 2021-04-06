
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
	
	sur::Instancer::Add(new sur::Rectangle({ 40,40 }, { 100,100 }, Color(255, 0, 0), "Rect", 0), Types::Rectangle);
	sur::Instancer::Add(new sur::Rectangle({ 100,253 }, { 100,100 }, Color(255, 0, 0), "Rect2", 0), Types::Rectangle);
	for (;;) {
		renderer.ClearScreenBuffer();
		sur::Instancer::Get<sur::Rectangle>(Types::Rectangle, "", 0)->Bind(true, true);
		sur::Instancer::Get<sur::Rectangle>(Types::Rectangle, "", 1)->Bind(true, true);
		if (_input.keyboard.Key(Keys::A)) {
			sur::Camera::Move({ -1, 0});
		}
		if (_input.keyboard.Key(Keys::D)) {
			sur::Camera::Move({ 1, 0 });
		}
		if (_input.keyboard.Key(Keys::W)) {
			sur::Camera::Move({ 0, -1 });
		}
		if (_input.keyboard.Key(Keys::S)) {
			sur::Camera::Move({ 0, 1 });
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
