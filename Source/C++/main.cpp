

#include "Functional/includes.h"
#include "Lua/SurLua.h"

extern void Window(const char* name,int params);
extern sur::Map_Analyses _Amap;
extern sur::Input _input;

using sur::Instancer::Types;


int main() {
	lua_State* L = lua::LoadFile("F:\\C++\\Engine\\Engine\\Source\\Lua\\config.lua");
	_debug = stoi(lua::GetTableContent(L,"configuration","debug"));
	_window_size(750, 750);
	_map = sur::Initialize();
	_Amap(_map, _window_size);
	
	Window("Fuck Adrian", WS_BORDER | WS_SYSMENU | WS_CAPTION);
	
	sur::Render renderer(Color(100, 107, 47),1);
	renderer.FPS();
	renderer.DebugConsole(true);
	int var = 0;
	for (int i = 0; i < 4; i++, var += 50) {
		sur::Instancer::Add(new sur::LoadObj("C:\\Users\\gero\\Desktop\\Hardcore Engine\\Hgineres\\survivalizeed.Hgineres", { var, 0 }, "shot" + std::to_string(i), 50), Types::Obj);
	}
	for (;;) {
		renderer.ClearScreenBuffer();
		for (int i = 0; i < 4; i++) {
			sur::Instancer::GetObj("shot" + std::to_string(i))->Bind(true, ColliderType::Outline);
		}
		if (_input.keyboard.Key(Keys::W))
			sur::Camera::Move({ 0,20 });
		if (_input.keyboard.Key(Keys::A))
			sur::Camera::Move({ -20,0 });
		if (_input.keyboard.Key(Keys::S))
			sur::Camera::Move({ 0,-20 });
		if (_input.keyboard.Key(Keys::D))
			sur::Camera::Move({ 20,0 });
		if (_input.keyboard.Key(Keys::F))
			sur::Instancer::GetObj("shot0")->Move({ 2,0 }, false);
		renderer.RenderScreenBuffer();
	}
}

