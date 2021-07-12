#include "../C++/Functional/includes.h"
#include "../C++/Functional/functional.h"
#include "../C++/Functional/TemporaryObjects.h"
#include "Game.h"

extern sur::Map_Analyses _Amap;
extern sur::Input _input;


void Splash(sur::Render& renderer) {
	sur::Object splash(_resource_path + "HgineSplash.hgineres", { 0,-9 }, "splash", 0);
	f32 tint = -250;
	bool negpos = false;
	sur::Sound(_sound_path + "IntroSound.wav", SND_ASYNC, 0x99999999);
	for (;;) {
		renderer.ClearScreenBuffer();
		splash.SetTint(sur::sRGB((i32)tint, (i32)tint, (i32)tint));
		splash.Bind(true, ColliderType::None);
		if (!negpos) tint += 0.6f;
		else tint -= 1.f;
		if (tint >= 0 && !negpos) {
			sleep_for(seconds(2));
			negpos = true;
		}
		if (tint <= -500 && negpos)
			return;
		renderer.RenderScreenBuffer();
	}
}