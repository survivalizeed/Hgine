
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

	sur::Render renderer(Color(0, 0, 0),true,1);
	renderer.DebugConsole(_debug);
	renderer.FPS();
	
	sur::ParticlesSetting set;
	for (int i = 20; i < 255; i++) {
		set.colors.push_back(Color(i/ 2, i, 255 ));
	}
	set.max_distance_to_middle = 200;
	set.emission = 50000;
	set.emission_point_min(250, 250);
	set.emission_point_max(250, 250);
	set.noise_factor = 2;
	set.block_directions.push_back(Direction::None);
	sur::Particles a(&set);

	i8 toggle = 0;
	for (;;) {
		renderer.ClearScreenBuffer();
		a.Bind(true);
		if(_input.mouse.RClick())
			a.MoveTowards(_input.mouse.Position(),3);
		set.middle = a.GetPosition();
		if (_input.keyboard.Key(Keys::A)) {
			sur::Vec2f dir(sur::Direction(_input.mouse.Position(), a.GetPosition()));
			a.Move(dir * 2);
		}
		if (_input.keyboard.Key(Keys::D)) {
			sur::Vec2f dir(sur::Direction(_input.mouse.Position(), a.GetPosition()));
			dir.invert();
			a.Move(dir * 2);
		}			
		if (_input.keyboard.Key(Keys::W))
			set.max_distance_to_middle++;
		if (_input.keyboard.Key(Keys::S))
			set.max_distance_to_middle--;
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
