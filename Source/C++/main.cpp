#include "Functional/includes.h"
#include "Functional/functional.h"
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

	sur::Instancer::Add(new sur::LoadObj(lua::GetTableContent(L,"configuration","ressouce_path") + "Space.Hgineres",
		{ 0,0 }, "Space", 100), Types::Obj);

	sur::Instancer::Add(new sur::LoadObj(lua::GetTableContent(L, "configuration", "ressouce_path") + "Player.Hgineres",
		{ 10,400}, "Player", 1), Types::Obj);
	
	sur::Instancer::Add(new sur::LoadObj(lua::GetTableContent(L, "configuration", "ressouce_path") + "Enemy.Hgineres",
		{0,10}, "Enemy", 2), Types::Obj);

	sur::Instancer::Add(new sur::LoadObj(lua::GetTableContent(L, "configuration", "ressouce_path") + "Shot.Hgineres",
		{ 0,0 }, "shot", 3), Types::Obj);

	sur::Instancer::Add(new sur::Line({ 0,0 }, { 0,_window_size.y - 1 },
		Color(0, 0, 0), "LineLeft", 4), Types::Line);
	
	sur::Instancer::Add(new sur::Line({ _window_size.x - 1,0 }, { _window_size.x - 1,_window_size.y - 1 },
		Color(0, 0, 0), "LineRight", 4), Types::Line);
	
	for (;;) {
		renderer.ClearScreenBuffer();				
		{
			sur::Instancer::GetObj("Space")->Bind(false, ColliderType::None);
			sur::Instancer::GetObj("Enemy")->Bind(true, ColliderType::Filled);
			sur::Instancer::GetObj("Player")->Bind(true, ColliderType::Filled);
			sur::Instancer::GetObj("shot")->Bind(true, ColliderType::Filled);
			sur::Instancer::GetLine("LineLeft")->Bind(true);
			sur::Instancer::GetLine("LineRight")->Bind(true);
		}
		{
			sur::MoveTowards((sur::Master*)(sur::Instancer::GetObj("Enemy")),
				(sur::Master*)sur::Instancer::GetObj("Player"), { 1,1 }, true);
		}
		{
			if (_input.keyboard.Key(Keys::A))
				sur::Instancer::GetObj("Player")->Move({ -3,0 }, true);
			if (_input.keyboard.Key(Keys::D))
				sur::Instancer::GetObj("Player")->Move({ 3,0 }, true);
		}
		renderer.RenderScreenBuffer();
	}
}



lua_State* Start() {
	lua_State* L = lua::LoadFile("F:\\C++\\Hgine\\Hgine\\Source\\Lua\\config.lua");
	
	_debug = stoi(lua::GetTableContent(L, "configuration", "debug_mode"));
	
	_window_size(stoi(lua::GetTableContent(L, "configuration", "window_size_x")),
		stoi(lua::GetTableContent(L, "configuration", "window_size_y")));

	_map = sur::Initialize();
	
	_Amap(_map, _window_size);
	
	//Create the Window with some parameters
	Window(lua::GetTableContent(L, "configuration", "application_name").c_str(), WS_OVERLAPPEDWINDOW);

	return L;
}





//if (_input.keyboard.Key(Keys::A))
//	sur::Instancer::GetObj("Player")->Move({ -3,0 }, true);
//if (_input.keyboard.Key(Keys::D))
//	sur::Instancer::GetObj("Player")->Move({ 3,0 }, true);
//if (_input.keyboard.Key(Keys::SPACE))
//	sur::Instancer::GetObj("shot")->SetPosition(sur::Instancer::GetObj("Player")->GetPosition());