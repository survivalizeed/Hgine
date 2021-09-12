

#include "Hgine/Includes.h"

using namespace sur;

int main() {

	wndInitialize(Vec2(1000, 750), Vec2(1000, 750), "", "");
	wndCreate("Hgine Demo", WS_OVERLAPPEDWINDOW);

	Renderer renderer(Color(0, 0, 0), true, 0.f, false);
	renderer.FPS();

	Form a({ {200,200}, {300, 200}, {300, 300}, {200,300}, {200,200} }, Form::Modifier::None, Color(255, 255, 255), "a");
	//Sprite b("C:\\Users\\gero\\Pictures\\forestrain.png", Sprite::FileType::PNG, { 0,0 }, "n");

	f32 angle1 = 0;
	f32 angle2 = 0;
	std::vector<Vec2f> original_points(a.points);
	for (;;) {
		renderer.Clear();
		a.Bind(true, false);
		
		for (i32 i = 0; i < a.points.size(); ++i) {
			a.points[i] = Rotate2D(original_points[i], { 250,250 }, (i32)angle1);
		}
		for (i32 i = 0; i < a.points.size(); ++i) {
			a.points[i] = Rotate2D(a.points[i], { 500,375 }, (i32)angle2);
		}
		angle1 += 0.4f;
		angle2 += 1.f;
		renderer.Render();
	}
}
