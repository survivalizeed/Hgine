

#include "Hgine/Includes.h"

using namespace sur;

int main() {

	hgineInitialize(Vec2(750, 750), Vec2(750, 750), "", "");
	wndCreate("Hgine Demo", WS_OVERLAPPEDWINDOW);

	Renderer renderer(Color(0, 0, 0), true, 0.f, false);
	renderer.FPS();

	Square s1({ 0, 0 }, { 100,100 }, Color(255, 255, 255), Collider::AABB, "s1");
	Square s2({ 150, 150 }, { 250,250 }, Color(255, 255, 255), Collider::AABB, "s2");
	Square s3({ 300,300 }, { 400,400 }, Color(255, 255, 255), Collider::AABB, "s3");

	s1.onCollisionEnter = [](GameObject* current, GameObject*) {
		oCEnterLockBegin(current);
		current->color = Color(255, 0, 0);
		oCEnterLockEnd(current);
	};

	s1.onCollisionExit = [](GameObject* current, GameObject*) {
		oCExitLockBegin(current);
		if(!current->anyCollisionLeft)
			current->color = Color(255, 255, 255);
		oCExitLockEnd(current);
	};

	s2.onCollisionEnter = [](GameObject* current, GameObject*) {
		oCEnterLockBegin(current);
		current->color = Color(255, 0, 0);
		oCEnterLockEnd(current);
	};

	s2.onCollisionExit = [](GameObject* current, GameObject*) {
		oCExitLockBegin(current);
		current->color = Color(255, 255, 255);
		oCExitLockEnd(current);
	};

	s3.onCollisionEnter = [](GameObject* current, GameObject*) {
		oCEnterLockBegin(current);
		current->color = Color(255, 0, 0);
		oCEnterLockEnd(current);
	};

	s3.onCollisionExit = [](GameObject* current, GameObject*) {
		oCExitLockBegin(current);
		current->color = Color(255, 255, 255);
		oCExitLockEnd(current);
	};

	for (;;) {
		renderer.Clear();
		s1.Bind(true);
		s2.Bind(true);
		s3.Bind(true);

		if (Input::Keyboard::KeyHeld(A))
			s1.Move({ -0.3f,0 }, 0);
		if (Input::Keyboard::KeyHeld(D))
			s1.Move({ 0.3f,0 }, 0);
		if (Input::Keyboard::KeyHeld(W))
			s1.Move({ 0,0.3f }, 0);
		if (Input::Keyboard::KeyHeld(S))
			s1.Move({ 0,-0.3f }, 0);

		if (Input::Keyboard::KeyHeld(J))
			s2.Move({ -0.3f,0 }, 0);
		if (Input::Keyboard::KeyHeld(L))
			s2.Move({ 0.3f,0 }, 0);
		if (Input::Keyboard::KeyHeld(I))
			s2.Move({ 0,0.3f }, 0);
		if (Input::Keyboard::KeyHeld(K))
			s2.Move({ 0,-0.3f }, 0);
		renderer.Render();
	}
}
