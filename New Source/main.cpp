

#include "Hgine/Includes.h"

using namespace sur;


int main() {

	wndInitialize(Vec2(750, 750), Vec2(750, 750), "", "");
	wndCreate("Hgine Demo", WS_OVERLAPPEDWINDOW);

	Renderer renderer(Color(0, 0, 0), true, 0.f, false);
	renderer.FPS();

	Sprite s("C:\\Users\\gero\\Pictures\\Adrian.png", Sprite::FileType::PNG, { 0,0 }, "n");

	std::vector<Vec2> backup(s.points);

	f32 angle = 0;
	for (;;) {
		renderer.Clear();
		s.Bind(true);
		for (i32 i = 0; i < s.points.size(); ++i) {
			backup[i] = ATS(Rotate2D(STA(backup[i]), {375, 375}, (i32)angle));
		}
		if(Input::Keyboard::KeyHeld(R))
			angle += 1.f;
		if (Input::Keyboard::KeyHeld(W)) {
			for (auto& iter : backup)
				iter += {0, 1};
		}
		if (Input::Keyboard::KeyHeld(A)) {
			for (auto& iter : backup)
				iter += {-1, 0};
		}
		if (Input::Keyboard::KeyHeld(S)) {
			for (auto& iter : backup)
				iter += {0, -1};
		}
		if (Input::Keyboard::KeyHeld(D)) {
			for (auto& iter : backup)
				iter += {1, 0};
		}
		for (i32 i = 0; i < backup.size(); i++)
			s.points[i] = backup[i];
		renderer.Render();
	}
}
