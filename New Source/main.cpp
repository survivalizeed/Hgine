

#include "Hgine/Includes.h"

using namespace sur;

int main() {

	wndInitialize(Vec2(500, 500), Vec2(500, 500), "", "");
	wndCreate("Hgine Demo", WS_OVERLAPPEDWINDOW);

	Renderer renderer(Color(0, 0, 0), true, 0.f, false);
	renderer.FPS();

	Sprite a("G:\\test.png", Sprite::FileType::PNG, { 0,0 }, "a");

	for (;;) {
		renderer.Clear();
		a.Bind(true);
		renderer.Render();
	}
}
