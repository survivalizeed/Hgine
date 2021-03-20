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

	sur::Instancer::Add(new sur::LoadObj("C:\\Users\\gero\\Desktop\\Hardcore Engine\\Hgineres\\Shot.Hgineres",
		{ 0,0 }, "shot", 3),Types::Obj);

	sur::Line left({ 1,1 }, { 1,_window_size.y - 1}, Color(255, 0, 0), "border", 50);
	sur::Line right({ _window_size.x - 20 ,1 }, { _window_size.x - 20,_window_size.y - 1}, Color(255, 0, 0), "border", 50);
	for (;;) {
		renderer.ClearScreenBuffer();		
		sur::Instancer::GetObj("Enemy")->Bind(true, ColliderType::Outline);
		sur::Instancer::GetObj("Player")->Bind(true, ColliderType::Outline);
		sur::Instancer::GetObj("shot")->Bind(true, ColliderType::Outline);
		left.Bind(true);
		right.Bind(true);
		if (_input.keyboard.Key(Keys::A))
			sur::Instancer::GetObj("Player")->Move({ -3,0 }, true);
		if (_input.keyboard.Key(Keys::D))
			sur::Instancer::GetObj("Player")->Move({ 3,0 }, true);
		if (_input.keyboard.Key(Keys::SPACE))
			sur::Instancer::GetObj("shot")->SetPosition(sur::Instancer::GetObj("Player")->GetPosition());

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