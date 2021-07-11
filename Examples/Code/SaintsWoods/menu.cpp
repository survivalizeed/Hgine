#include "../C++/Functional/includes.h"
#include "../C++/Functional/functional.h"
#include "../C++/Functional/TemporaryObjects.h"
#include "Game.h"

extern sur::Map_Analyses _Amap;
extern sur::Input _input;


void Menu(sur::Render& renderer) {
	
	using namespace sur::Instancer;

	sur::SetVolume(0x66666666);
	Audio audio;
	audio.Play(_sound_path + "menu_music.mp3");

	sur::Object background(_resource_path + "menu.Hgineres", { 0,0 }, "background", 0);
	sur::Object play(_resource_path + "Menu\\Play.Hgineres", { 30,60 }, "play", 1);
	sur::Object quit(_resource_path + "Menu\\Quit.Hgineres", { 30,35 }, "quit", 2);

	f32 scaler = 0.8f;
	i32 rot = 0;
	bool down = true;

	for (;;) {
		renderer.ClearScreenBuffer();
		background.Bind(true, ColliderType::None);

		play.Bind(true, ColliderType::Filled);
		quit.Bind(true, ColliderType::Filled);

		play.Scale({ scaler, scaler });
		quit.Scale({ scaler,scaler });

		if (down) {
			scaler -= 0.001f;
			play.Move({ 0.15f,0.08f }, false);
			quit.Move({ 0.15f,0.08f }, false);
		}
		else {
			scaler += 0.001f;
			play.Move({ -0.15f,-0.08f }, false);
			quit.Move({ -0.15f,-0.08f }, false);
		}

		if (scaler >= 0.7f)
			down = true;
		else if (scaler <= 0.5f)
			down = false;

		if (_Amap.Collider.Get2d(ATS(_input.mouse.Position()).x, ATS(_input.mouse.Position()).y) == 1) {
			play.SetTint({ 255,0,0 });
			if (_input.mouse.LClick())
				return;
		}
		else
			play.SetTint({ 0,0,0 });

		if (_Amap.Collider.Get2d(ATS(_input.mouse.Position()).x, ATS(_input.mouse.Position()).y) == 2) {
			quit.SetTint({ 255,0,0 });
			if (_input.mouse.LClick())
				exit(0);
		}
		else
			quit.SetTint({ 0,0,0 });

		renderer.RenderScreenBuffer();
	}

}