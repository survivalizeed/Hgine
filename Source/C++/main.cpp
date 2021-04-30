// SpaceShooter demo -> paste this into the main

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

	sur::Render renderer(Color(100, 107, 47), true,0);
	renderer.DebugConsole(_debug);
	renderer.FPS();

	//sur::Object a(_resource_path + "player.hgineres", { 10,10 }, "pp", 12);

	//sur::Triangle a({ 20,20 }, { 100,100 }, { 100,0 }, Color(255, 0, 0), "Tri", 1);
	//sur::Triangle b({ 200,200 }, { 300,200 }, { 200,300 }, Color(255, 0, 0), "Tri", 2);
	//sur::Line a({ 20,20 }, { 100,100 }, Color(255, 0, 0), "t", 1);
	//sur::Line b({ 100,200 }, { 100,100 }, Color(255, 0, 0), "t", 2);
	sur::Shape a(Color(25, 234, 22), "adf", 2);
	a.Pass(sur::Vec2(10, 10), sur::Vec2(50, 80), sur::Vec2(100, 300), sur::Vec2(30, 100));

	for (;;) {
		renderer.ClearScreenBuffer();	
		a.Bind(true, true);
		
		if (_input.keyboard.Key(Keys::W)){
			a.Move({ 0,1 });
		}
		if (_input.keyboard.Key(Keys::A)){
			a.Move({ -1,0 });
		}
		if (_input.keyboard.Key(Keys::S)){
			a.Move({ 0,-1 });
		}
		if (_input.keyboard.Key(Keys::D)){
			a.Move({ 1,0 });
		}
		if (_input.mouse.RClick()) {
			a.SetPosition(3, _input.mouse.Position());
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