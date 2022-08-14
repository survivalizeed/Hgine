#include "Hgine/Includes.h"

using namespace sur;
using namespace sur::Manager;

void changeLight() {
	for (;;) {
		Sleep(100);
		Get<Light>("light")->color = Color(RandomRange(50, 255), RandomRange(50, 255), RandomRange(50, 255));
	}
}

int main() {

	hgineInitialize(Vec2(1000, 750), Vec2(1000, 750), "", "");
	wndCreate("Hgine Demo", WS_OVERLAPPEDWINDOW);

	Renderer renderer(Color(0, 0, 0), true, 0.f, true);
	renderer.FPS();

	new Square({0.f,0.f}, {1000.f, 750.f}, Color(255,255,255), "square");
	new Form({}, {}, Form::Modifier::InverseKinematic, Form::FillMode::Index, RenderMode::Wireframe, Color(255,255,255), "form");
	for (int i = 0; i < 3000; ++i) {
		Get<Form>("form")->points.push_back(Vec2f((float)i, 700));
	}
	new Light({0.f,0.f}, 100000.f, 50000.f, 20.f, Color(0, 0, 255), "light");

	std::thread t1(changeLight);
	t1.detach();

	for (;;) {
		renderer.Clear();
		if (Input::LClickHeld()) {
			Get<Form>("form")->SetPoint(2999, Input::Position().value_or(Vec2f(0.f,0.f)));
		}
		Get<Light>("light")->SetPosition(Input::Position().value_or(Vec2f(0.f, 0.f)));
		Get<Form>("form")->Bind();
		renderer.Render();
	}
}
