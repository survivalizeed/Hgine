#include "Functional/includes.h"
#include "Lua/SurLua.h"

lua_State* Start();
extern void Window(const char* name, int params);
extern sur::Map_Analyses _Amap;
extern sur::Input _input;

using sur::Instancer::Types;


int main() {
	lua_State* L = Start();
	
	sur::Render renderer(Color(100, 107, 47), 1);
	renderer.DebugConsole(_debug);
	renderer.FPS();
	
	sur::Instancer::Add(new sur::LoadObj("C:\\Users\\gero\\Desktop\\Hardcore Engine\\Hgineres\\Player.Hgineres",
		{ 0,350 }, "Player", 1), Types::Obj);
	
	sur::Instancer::Add(new sur::LoadObj("C:\\Users\\gero\\Desktop\\Hardcore Engine\\Hgineres\\Enemy.Hgineres",
		{0,0}, "Enemy", 2), Types::Obj);

	for (;;) {
		renderer.ClearScreenBuffer();		
		sur::Instancer::GetObj("Enemy")->Bind(true, ColliderType::Outline);
		sur::Instancer::GetObj("Player")->Bind(true, ColliderType::Outline);
		if (_input.keyboard.Key(Keys::W))
			sur::Instancer::GetObj("Player")->Move({ 0,3 }, true);
		if (_input.keyboard.Key(Keys::A))
			sur::Instancer::GetObj("Player")->Move({ -3,0 }, true);
		if (_input.keyboard.Key(Keys::S))
			sur::Instancer::GetObj("Player")->Move({ 0,-3 }, true);
		if (_input.keyboard.Key(Keys::D))
			sur::Instancer::GetObj("Player")->Move({ 3,0 }, true);
		renderer.RenderScreenBuffer();
	}
}



lua_State* Start() {
	lua_State* L = lua::LoadFile("F:\\C++\\Engine\\Engine\\Source\\Lua\\config.lua");
	
	_debug = stoi(lua::GetTableContent(L, "configuration", "debug_mode"));
	
	/*_window_size(stoi(lua::GetTableContent(L, "configuration", "window_size_x")),
		stoi(lua::GetTableContent(L, "configuration", "window_size_y")));*/

	_window_size({ 500,500 });

	_map = sur::Initialize();
	
	_Amap(_map, _window_size);
	
	//Create the Window with some parameters
	Window(lua::GetTableContent(L, "configuration", "application_name").c_str(), WS_BORDER | WS_SYSMENU | WS_CAPTION);

	return L;
}