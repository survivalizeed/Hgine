

#include "Hgine/Includes.h"

using namespace sur;

int main() {

	hgineInitialize(Vec2(750, 750), Vec2(750, 750), "", "");
	wndCreate("Hgine Demo", WS_OVERLAPPEDWINDOW);

	Renderer renderer(Color(0, 0, 0), false, 0.f, true);
	renderer.FPS();

	Square s1({ 0, 0 }, { 750,750 }, Color(255, 255, 255), Collider::AABB, "s1");
	
	Light s({ 750 / 2, 750 / 2 }, 0.f, 5000.f, 0.f, Color(255, 255, 0), "s");

	Light greenblue({ 200,200 }, 0.f, 20000.f, 5.f, Color(0, 255, 255), "greenblue");

	Light blue({ 200,200 }, 0.f, 20000.f, 5.f, Color(0, 0, 255), "blue");

	Light green({ 200,200 }, 0.f, 20000.f, 5.f, Color(0, 255, 0), "green");

	Light red({ 200,200 }, 0.f, 20000.f, 5.f, Color(255, 0, 0), "red");

	Light pink({ 200,200 }, 0.f, 20000.f, 5.f, Color(255, 0, 255), "pink");

	f32 greenblueStartangle = 0.f;
	f32 greenStartangle = 90.f;
	f32 redStartangle = 180.f;
	f32 pinkStartangle = 270.f;
	f32 blueStartangle = 45.f;

	for (;;) {
		renderer.Clear();
		s1.Bind(true);

		greenblue.position = Rotate2D({ 200,200 }, { 750 / 2, 750 / 2 }, (i32)greenblueStartangle);
		green.position = Rotate2D({ 200,200 }, { 750 / 2, 750 / 2 }, (i32)greenStartangle);
		red.position = Rotate2D({ 200,200 }, { 750 / 2, 750 / 2 }, (i32)redStartangle);
		pink.position = Rotate2D({ 200,200 }, { 750 / 2, 750 / 2 }, (i32)pinkStartangle);
		blue.position = Rotate2D({ 200,200 }, { 750 / 2, 750 / 2 }, (i32)blueStartangle);
		if (Input::Keyboard::KeyHeld(A)) {
			greenblue.threshold -= 1000;
			green.threshold -= 1000;
			red.threshold -= 1000;
			pink.threshold -= 1000;
			blue.threshold -= 1000;
		}
		if (Input::Keyboard::KeyHeld(D)) {
			greenblue.threshold += 1000;
			green.threshold += 1000;
			red.threshold += 1000;
			pink.threshold += 1000;
			blue.threshold += 1000;
		}

		greenblueStartangle += 2.0f;
		greenStartangle += 1.0f;
		redStartangle += 1.5f;
		pinkStartangle += 2.5f;
		blueStartangle += 3.f;

		renderer.Render();
	}
}
