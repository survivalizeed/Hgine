

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

	sur::Render renderer(Color(0, 0, 0),true,0);
	renderer.DebugConsole(true);
	renderer.FPS();

	sur::Object a(_resource_path + "player.hgineres", { 50, 50 }, "hallo", 12);

	for (int i = 0; i < 10; i++) {
		sur::Instancer::Add(new sur::Object(&a, { i * 10, i * 10 }, "helo" + std::to_string(i), 1), Types::Object);
	}

	f32 inc = 1.f;
	f32 incy = 1.f;

	u64 milliseconds = 0;
	for (;;) {
		renderer.ClearScreenBuffer();
		a.Bind(true, ColliderType::Outline);
		if (sur::GetMilliseconds() - milliseconds > Second / 100) {
			
			a.MoveBeta({ 1.f,0.f }, false);
			milliseconds = sur::GetMilliseconds();
		}
		//for (int i = 0; i < 2; i++) {
		//	sur::Instancer::Get<sur::Object>("helo" + std::to_string(i))->Bind(true, ColliderType::Outline);
		//}
		//a.Bind(true, ColliderType::Outline);
		//a.Scale({ inc,incy });
		//if (_input.keyboard.Key(Keys::A)) {
		//	inc -= 0.01f;
		//}
		//if (_input.keyboard.Key(Keys::D)) {
		//	inc += 0.01f;
		//}
		//if (_input.keyboard.Key(Keys::W)) {
		//	incy += 0.01f;
		//}
		//if (_input.keyboard.Key(Keys::S)) {
		//	incy -= 0.01f;
		//}
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
