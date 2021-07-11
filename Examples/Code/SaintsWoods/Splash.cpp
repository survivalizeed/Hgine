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
	for (;;) {
		renderer.ClearScreenBuffer();
		splash.SetTint(sur::sRGB((i32)tint, (i32)tint, (i32)tint));
		splash.Bind(true, ColliderType::None);
		if (!negpos) tint += 0.3f;
		else tint -= 0.3f;
		if (tint >= 0 && !negpos) {
			negpos = true;
		}
		if (tint <= -250 && negpos)
			return;
		renderer.RenderScreenBuffer();
	}
}