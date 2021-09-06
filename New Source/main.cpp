

#include "Hgine/Includes.h"

using namespace sur;

int main() {

	wndInitialize(Vec2(500, 500), Vec2(500, 500), "", "");
	wndCreate("Hgine Demo", WS_OVERLAPPEDWINDOW);

	Renderer renderer(Color(0, 0, 0), true, 0.f, false);
	renderer.FPS();

	Form form({ { 100, 100 }, {150,150}, { 200, 200 }, {250,250}, {250,250}, {300,300}, {350, 350} }, Color(255, 0, 0), "f");

	Vec2f beginStart(150, 150);
	Vec2f beginEnd(200, 200);
	Vec2f start(250, 250);
	Vec2f end(300, 300);
	Vec2f last1(0, 0);
	Vec2f last2(0, 0);

	f32 segFirst = (beginStart - beginEnd).magnitude();
	f32 segLast = (start - end).magnitude();

	auto LookAt = [&](Vec2f line_start, Vec2f line_end, Vec2f target, f32 length) -> Vec2f {
		Vec2f direction(target - line_start);
		direction.normalize();
		return direction * length + line_start;
	};

	for (;;) {
		renderer.Clear();
		form.Bind(true, true);
		if (Input::Mouse::RClick())
			form.SetPoint(0, Input::Mouse::Position(), true);

		renderer.Render();
	}
}
//Vec2f mPos = Input::Mouse::Position();


//Vec2f transEnd = LookAt(start, end, mPos, segLast);
//
//last2 = mPos - transEnd;

//start = start + last2;

//algorithm::DrawLine(start, transEnd + last2, Color(255, 0, 0), nullptr, nullptr);


//transEnd = LookAt(beginStart, beginEnd, start, segFirst);

//last1 = start - transEnd;

//beginStart = beginStart + last1;

//algorithm::DrawLine(beginStart, transEnd + last1, Color(0,255, 0), nullptr, nullptr);