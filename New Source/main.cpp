#include "Hgine/Includes.h"

using namespace sur;


int main() {

	wndInitialize(Vec2(750, 750), Vec2(750, 750), "", "");
	wndCreate("Hgine Demo", WS_OVERLAPPEDWINDOW);

	Renderer renderer(Color(0, 0, 0), true, 0.f, false);
	renderer.FPS();

	ParticleSettings3D settings;
	for (i32 i = 0; i < 255; ++i)
		settings.colors.push_back(Color(70, i, i / 2));
	settings.emission = 100000;
	settings.emission_point_minimal(100, 100, 100);
	settings.emission_point_maximal(300, 300, 300);
	settings.max_distance_to_middle = 200.f;
	settings.min_distance_to_middle = 100.f;
	settings.min_noise = 1;
	settings.max_noise = 20;
	settings.origin(200, 200, 200);

	ParticleSystem3D sys(&settings);

	f32 angleX = 0;
	f32 angleY = 0;
	f32 angleZ = 0;

	for (;;) {
		renderer.Clear();
		sys.Bind(true, 300);

		if (Input::Keyboard::KeyHeld(J)) {
			sys.Rotate(Dimension::X, (i32)angleX);
			angleX += 2.f;
		}
		if (Input::Keyboard::KeyHeld(K)) {
			sys.Rotate(Dimension::Y, (i32)angleY);
			angleY += 2.f;
		}
		if (Input::Keyboard::KeyHeld(L)) {
			sys.Rotate(Dimension::Z, (i32)angleZ);
			angleZ += 2.f;
		}		
		if (Input::Keyboard::KeyHeld(W))
			sys.Move({ 0,0,1 });
		if (Input::Keyboard::KeyHeld(A))
			sys.Move({ -1,0,0 });
		if (Input::Keyboard::KeyHeld(S))
			sys.Move({ 0,0,-1 });
		if (Input::Keyboard::KeyHeld(D))
			sys.Move({ 1,0,0 });
		if (Input::Keyboard::KeyHeld(E))
			settings.max_distance_to_middle -= 0.5f;
		if (Input::Keyboard::KeyHeld(Q))
			settings.max_distance_to_middle += 0.5f;

		renderer.Render();
	}

}
