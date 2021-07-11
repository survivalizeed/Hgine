// SpaceShooter demo -> paste this into the main




// ===================!Code could be outdated!===================






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
	static lua_State* LG = lua::LoadFile("F:\\C++\\Hgine\\Hgine\\Source\\Lua\\game.lua"); //static, so the lambda won't cry

	sur::Render renderer(Color(100, 107, 47), 1);
	renderer.DebugConsole(_debug);
	renderer.FPS();

	sur::Instancer::Add(new sur::Object(_resource_path + "Space.Hgineres", { 0,0 }, "Space", 100), Types::Object);

	sur::Instancer::Add(new sur::Object(_resource_path + "Player.Hgineres", { 10,400 }, "Player", 1), Types::Object);

	sur::Instancer::Add(new sur::Object(_resource_path + "Enemy.Hgineres", { 0,10 }, "Enemy", 2), Types::Object);

	sur::Instancer::Add(new sur::Object(_resource_path + "Shot.Hgineres", { 0,0 }, "Shot", 3), Types::Object); // <- prefab for shots

	sur::Instancer::Add(new sur::Object(_resource_path + "ShotE.Hgineres", { 0,0 }, "ShotE", 4), Types::Object);

	sur::Instancer::Add(new sur::Line({ 0,0 }, { 0,_window_size.y - 1 }, Color(0, 0, 0), "LineLeft", 4), Types::Line);

	sur::Instancer::Add(new sur::Line({ _window_size.x - 1,0 }, { _window_size.x - 1,_window_size.y - 1 },
		Color(0, 0, 0), "LineRight", 4), Types::Line);

	sur::Instancer::Add(new sur::Line({ 0,333 }, { _window_size.x,333 }, Color(0, 0, 0), "LineTop", 4), Types::Line);

	sur::Instancer::Add(new sur::Line({ 0,_window_size.y - 1 }, { _window_size.x,_window_size.y - 1 },
		Color(0, 0, 0), "LineBottom", 4), Types::Line);

	i32 shotvar = 0, shotenemyvar = 0;

	i64 delay = sur::GetMilliseconds();
	i64 snapshot = delay;

	i64 enemydelay = delay;
	i64 enemysnapshot = delay;

	for (;;) {
		renderer.ClearScreenBuffer();
		{
			sur::Instancer::Get<sur::Object>("Space")->Bind(true, false, ColliderType::None);
			sur::Instancer::Get<sur::Object>("Enemy")->Bind(true, true, ColliderType::Filled);
			sur::Instancer::Get<sur::Object>("Player")->Bind(true, true, ColliderType::Filled);
			sur::Instancer::Get<sur::Line>("LineLeft")->Bind(false, true);
			sur::Instancer::Get<sur::Line>("LineRight")->Bind(false, true);
			sur::Instancer::Get<sur::Line>("LineTop")->Bind(false, true);
			sur::Instancer::Get<sur::Line>("LineBottom")->Bind(false, true);
			for (i16 i = 0; i < shotvar; ++i) {
				sur::Object* tmp = sur::Instancer::Get<sur::Object>("CloneShot" + std::to_string(i));
				if (abs(tmp->GetPosition().x) > 1000 || abs(tmp->GetPosition().y) > 1000)
					sur::Instancer::State(Types::Object, false, "CloneShot" + std::to_string(i));
				tmp->Bind(true, true, ColliderType::Filled);
				tmp->Move({ 0,-4 }, true);
			}
			for (i16 i = 0; i < shotenemyvar; ++i) {
				sur::Object* tmp = sur::Instancer::Get<sur::Object>("CloneShotE" + std::to_string(i));
				if (abs(tmp->GetPosition().x) > 1000 || abs(tmp->GetPosition().y) > 1000)
					sur::Instancer::State(Types::Object, false, "CloneShotE" + std::to_string(i));
				tmp->Bind(true, true, ColliderType::Filled);
				tmp->Move({ 0,8 }, true);
			}
		}
		{
			sur::MoveTowards((sur::Master*)(sur::Instancer::Get<sur::Object>("Enemy")),
				(sur::Master*)sur::Instancer::Get<sur::Object>("Player"), 1, Axis::X, true);
		}
		{	//=====Enemy=====
			using namespace sur::Instancer;
			if (sur::Distance<Axis::X>(Get<sur::Object>("Player"), Get<sur::Object>("Enemy")) <= 50
				&& enemydelay - enemysnapshot >= 250) {
				sur::Sound((_sound_path + "EnemyShot.wav").c_str(), SND_ASYNC, 0x22222222);
				Add(new sur::Object(Get<sur::Object>("ShotE"), { Get<sur::Object>("Enemy")->GetPosition().x + 37,
					Get<sur::Object>("Enemy")->GetPosition().y + 78 },
					"CloneShotE" + std::to_string(shotenemyvar), shotenemyvar + 1000, { 4 },
					[](sur::Master* current, sur::Master* other) {
						if (other->GetName() == "Player")
							MessageBoxA(NULL, "You got hit", "You are Dead", MB_ICONINFORMATION);
					}), Types::Object);
				shotenemyvar++;
				enemysnapshot = enemydelay;
			}
		}
		{	//=====Player=====
			using namespace sur::Instancer;
			if (_input.keyboard.Key(Keys::A))
				Get<sur::Object>("Player")->Move({ -3,0 }, true);
			if (_input.keyboard.Key(Keys::D))
				Get<sur::Object>("Player")->Move({ 3,0 }, true);
			if (_input.keyboard.Key(Keys::W))
				Get<sur::Object>("Player")->Move({ 0,-3 }, true);
			if (_input.keyboard.Key(Keys::S))
				Get<sur::Object>("Player")->Move({ 0,3 }, true);
			if (_input.keyboard.Key(Keys::SPACE) && delay - snapshot >= 150) {
				static int hit = 0;
				sur::Sound((_sound_path + "PlayerShot.wav").c_str(), SND_ASYNC, 0x22222222);
				Add(new sur::Object(Get<sur::Object>("Shot"), { Get<sur::Object>("Player")->GetPosition().x + 40,
					Get<sur::Object>("Player")->GetPosition().y - 35 }, "CloneShot" + std::to_string(shotvar),
					-shotvar - 1000, { 4,1 },
					// OnCollision for the shot. obj will be the other object
					[](sur::Master* current, sur::Master* other) {
						if (other->GetName() == "Enemy") {
							hit++;
							current->active = false;
							if (hit >= stoi(lua::GetContent(LG, "enemy_lives"))) {
								MessageBoxA(NULL, (lua::GetContent(LG, "enemy_lives") + " Hits").c_str(),
									(lua::GetContent(LG, "enemy_lives") + " Hits").c_str(), MB_ICONINFORMATION);
								other->active = false;
							}
						}
					}
				), Types::Object);
				shotvar++;
				snapshot = delay;
			}
		}
		delay = sur::GetMilliseconds();
		enemydelay = sur::GetMilliseconds();
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
