

#include "Hgine/Includes.h"

using namespace sur;

int main() {

	hgineInitialize(Vec2(750, 750), Vec2(750, 750), "", "");
	wndCreate("Hgine Demo", WS_OVERLAPPEDWINDOW);

	Renderer renderer(Color(0, 0, 0), false, 0.1f, true);
	renderer.FPS();

	Square s1({ 0, 0 }, { 750,750 }, Color(255, 255, 255), Collider::AABB, "s1");
	
	Light s({ 0,0 }, 0.f, 10000.f, 10.f, Color(255, 255, 0));

	Light ss({ 0,0 }, 0.f, 10000.f, 10.f, Color(0, 255, 255));

	for (;;) {
		renderer.Clear();
		s1.Bind(true);

		if (Input::Mouse::RClick())
			s.position = Input::Mouse::Position();
		if (Input::Mouse::LClick())
			ss.position = Input::Mouse::Position();

		if (Input::Keyboard::KeyHeld(A))
			s1.Move({ -0.3f,0 }, 0);
		if (Input::Keyboard::KeyHeld(D))
			s1.Move({ 0.3f,0 }, 0);
		if (Input::Keyboard::KeyHeld(W))
			s1.Move({ 0,0.3f }, 0);
		if (Input::Keyboard::KeyHeld(S))
			s1.Move({ 0,-0.3f }, 0);
		renderer.Render();
	}
}
