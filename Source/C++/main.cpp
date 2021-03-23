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

	sur::Instancer::Add(new sur::Object(lua::GetTableContent(L, "configuration", "ressource_path") + "Space.Hgineres",
		{ 0,0 },"Shot",1),Types::Obj);

	sur::Instancer::Add(new sur::Object(sur::Instancer::GetObj("Shot"), { 30,30 },"Shot2",1), Types::Obj);
	sur::Instancer::Add(new sur::Object(sur::Instancer::GetObj("Shot"), { 40,30 }, "Shot3", 1), Types::Obj);

	for (;;) {
		renderer.ClearScreenBuffer();
		sur::Instancer::GetObj("Shot")->Bind(false, ColliderType::None);
		sur::Instancer::GetObj("Shot2")->Bind(false, ColliderType::None);
		sur::Instancer::GetObj("Shot3")->Bind(false, ColliderType::None);

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
