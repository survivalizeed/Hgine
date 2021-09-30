

#include "Hgine/Includes.h"

using namespace sur;


int main() {

	wndInitialize(Vec2(750, 750), Vec2(750, 750), "", "");
	wndCreate("Hgine Demo", WS_OVERLAPPEDWINDOW);

	Renderer renderer(Color(0, 0, 0), true, 0.f, false);
	renderer.FPS();
	
	sur::ParticleSettings settings;
	for (i32 i = 0; i < 255; ++i)
		settings.colors.push_back(Color(10, i, i / 2));
	settings.emission = 50000;
	settings.emission_point_minimal(350, 350);
	settings.emission_point_maximal(400, 400);
	settings.min_noise = 1;
	settings.max_noise = 4;
	settings.min_distance_to_middle = 50.f;
	settings.max_distance_to_middle = 200.f;

	sur::ParticleSystem system(&settings);

	sur::ParticleSettings settings2;
	for (i32 i = 0; i < 255; ++i)
		settings2.colors.push_back(Color(10, i32(i / 1.4f), i));
	settings2.emission = 5000;
	settings2.emission_point_minimal(350, 350);
	settings2.emission_point_maximal(400, 400);
	settings2.min_noise = 1;
	settings2.max_noise = 5;
	settings2.max_distance_to_middle = 50.f;


	sur::ParticleSystem system2(&settings2);

	for (;;) {
		renderer.Clear();

		system.Bind(true);
		system2.Bind(true);
		if (Input::Mouse::RClick()) {
			Vec2f pos = Vec2f(sur::RandomRange(0, 750), sur::RandomRange(0, 750));
			system.MoveTowards(pos, 0, 4, 6);
			system2.MoveTowards(pos, 0, 4, 6);
		}
		

		renderer.Render();
	}
	
}
