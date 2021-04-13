
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

	sur::Render renderer(Color(100, 107, 47),false,1);
	renderer.DebugConsole(_debug);
	renderer.FPS();
	i32 ti = 0;

	sur::Instancer::Add(new sur::Object(_resource_path + "survivalizeed.hgineres", { 100,100 }, "sur", 1), Types::Object);
	for (;;) {
		renderer.ClearScreenBuffer();
		sur::Instancer::Get<sur::Object>("sur")->Bind(true, ColliderType::None);
		if (_input.keyboard.Key(Keys::W)) {
			sur::Instancer::Get<sur::Object>("sur")->Move({ 0,-1 }, true);
		}
		if (_input.keyboard.Key(Keys::A)) {
			sur::Instancer::Get<sur::Object>("sur")->Move({ -1,0 }, true);
		}
		if (_input.keyboard.Key(Keys::S)) {
			sur::Instancer::Get<sur::Object>("sur")->Move({ 0,1 }, true);
		}
		if (_input.keyboard.Key(Keys::D)) {
			sur::Instancer::Get<sur::Object>("sur")->Move({ 1,0 }, true);
		}
		if (_input.keyboard.Key(Keys::G)) {
			--ti;
			sur::Instancer::Get<sur::Object>("sur")->Tint(sur::sRGB(0, ti, 0));	//Tint is not finished yet
			Sleep(100);
		}
		if (_input.keyboard.Key(Keys::H)) {
			++ti;
			sur::Instancer::Get<sur::Object>("sur")->Tint(sur::sRGB(0, ti, 0));
			Sleep(100);
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
