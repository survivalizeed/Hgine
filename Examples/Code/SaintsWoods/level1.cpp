#include "../C++/Functional/includes.h"
#include "../C++/Functional/functional.h"
#include "../C++/Functional/TemporaryObjects.h"
#include "Game.h"

extern sur::Map_Analyses _Amap;
extern sur::Input _input;

void Level1(sur::Render& renderer) {

	using namespace sur::Instancer;

	sur::SetVolume(0x44444444);
	Audio audio;
	//audio.Play(_sound_path + "game_music.mp3");

	bool gravity = true, jumping = false, canJump = true;

	i32 jumpFramesCounter = 0;

	f32 grav = 1.1f;
	f32 m = 4.f;

	i64 snap = sur::GetMilliseconds();


	// Prefabs AND Singles
	{
		SINGLE Add(new sur::Object(_resource_path + "galaxy.hgineres", { 0, Unit(116) }, "sky", 0),
			Types::Object);
		SINGLE Add(new sur::Object(_resource_path + "woods.hgineres", { 0,0 }, "woods", 0),
			Types::Object);
		SINGLE Add(new sur::Object(_resource_path + "blood.hgineres", { 0,0 }, "blood", 0),
			Types::Object);
		State(Types::Object, false, "blood");	//Disable the blood by default
		SINGLE Add(new sur::Object(_resource_path + "player.hgineres", { 50,50 }, "player", 2, { 0 }, { 0 },
			[&](sur::Master* current, sur::Master* other) {
				grav = 1.1f;
				canJump = true;
			}
		), Types::Object);

		PREFAB Add(new sur::Object(_resource_path + "grass_platform.hgineres", { 0,0 }, "platform1_prefab", 0),
			Types::Object);
		PREFAB Add(new sur::Object(_resource_path + "grass_platform_fly.hgineres", { 0,0 }, "platform2_prefab", 0),
			Types::Object);
		PREFAB Add(new sur::Object(_resource_path + "rock.hgineres", { 0,0 }, "rock_prefab", 0),
			Types::Object);
		PREFAB Add(new sur::Object(_resource_path + "monster.hgineres", { 0,0 }, "monster_prefab", 0),
			Types::Object);
	}


	sur::Line line({ 0,0 }, { 100,0 }, Color(255, 0, 0), "line", 4, { 0 },
		[](sur::Master* current, sur::Master* other) {
			if (other->GetName() == "player") {
				saints::Kill("player");
			}
		}
	);


	// The loading stuff. Collapse this if you want
	{
		for (i32 i = 0; i < 4; ++i) {
			if (i == 0)
				GAMEOBJECT Add(
					new sur::Object(
						Get<sur::Object>("platform1_prefab"),
						{ -4,0 - Unit(10) },
						"platform1_" + std::to_string(i),
						5,
						{ 4,5 }
					),
					Types::Object);
			else
				GAMEOBJECT Add(
					new sur::Object(
						Get<sur::Object>("platform1_prefab"),
						{ 0 + Get<sur::Object>("platform1_" + std::to_string(i - 1))->GetSize().x
						+ Get<sur::Object>("platform1_" + std::to_string(i - 1))->GetPosition().x,0 - Unit(10) },
						"platform1_" + std::to_string(i),
						5,
						{ 4,5 }
					),
					Types::Object);
		}
		GAMEOBJECT Add(new sur::Object(Get<sur::Object>("platform2_prefab"), { 80,20 }, "platform2_1", 5, { 4,5 }),
			Types::Object);

		GAMEOBJECT Add(new sur::Object(Get<sur::Object>("platform2_prefab"), { 130,20 }, "platform2_2", 5, { 4,5 }),
			Types::Object);

		GAMEOBJECT Add(new sur::Object(Get<sur::Object>("rock_prefab"), { -50,0 }, "rock", 5, { 4,5 }, { 0 },
			[](sur::Master* current, sur::Master* other) {
				l(other->GetName());
			}),
			Types::Object);
		GAMEOBJECT Add(new sur::Object(Get<sur::Object>("monster_prefab"), { 50,50 }, "monster", 5, { 4 }),
			Types::Object);
	}


	for (;;) {
		renderer.ClearScreenBuffer();

		saints::WallpaperScroll(*Get<sur::Object>("sky"));
		saints::WallpaperScroll(*Get<sur::Object>("woods"));
		
		line.Bind(false, true);

		Get<sur::Object>("rock")->Bind(true, ColliderType::Outline);

		for (i32 i = 0; i < 10; ++i)
			Get<sur::Object>("platform1_" + std::to_string(i))->Bind(true, ColliderType::Outline);

		Get<sur::Object>("platform2_1")->Bind(true, ColliderType::Outline);

		Get<sur::Object>("platform2_2")->Bind(true, ColliderType::Outline);

		Get<sur::Object>("player")->Bind(true, ColliderType::Outline);

		Get<sur::Object>("blood")->Bind(true, ColliderType::None);

		Get<sur::Object>("monster")->Bind(true, ColliderType::None);

		// Put all the logical stuff in this if statement. It is frame rate independent
		if (sur::GetMilliseconds() - snap >= _milliseconds(8)) {

			//saints::Gravity(Get<sur::Object>("player"), &grav, gravity);

			saints::Controls(Get<sur::Object>("woods"), Get<sur::Object>("sky"), 2.5f);

			//sur::MoveTowards(Get<sur::Object>("monster"), Get<sur::Object>("player"), 5.f, Axis::X, false);

			//if (_input.keyboard.Key(Keys::W))
				//Get<sur::Object>("player")->Move({ 0,2 }, true);
				//saints::Jump(Get<sur::Object>("woods"), Get<sur::Object>("sky"), 4, -1);
			//if (_input.keyboard.Key(Keys::S))
				//Get<sur::Object>("player")->Move({ 0,-2 }, true);
				//saints::Jump(Get<sur::Object>("woods"), Get<sur::Object>("sky"), 4, 1);
			if ((_input.keyboard.KeyDown(Keys::SPACE) || jumping) && canJump) {
				if (!jumping) {
					m = 9.f;
					gravity = false;
					jumping = true;
				}
				m -= (m / 20);
				//saints::Jump(Get<sur::Object>("woods"), Get<sur::Object>("sky"), m/ 2, -1);
				//(void)Get<sur::Object>("player")->Move({ 0, m * 1.5f}, true);
				jumpFramesCounter++;
				if (jumpFramesCounter >= 20) {
					jumpFramesCounter = 0;
					jumping = false;
					gravity = true;
					canJump = false;
				}
			}
			snap = sur::GetMilliseconds();
		}
		renderer.RenderScreenBuffer();
	}
	ClearAll();
}