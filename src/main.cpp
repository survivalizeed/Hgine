

#include "includes.h"

extern void Window();
extern sur::Map_Analyses _Amap;
extern sur::Input _input;

int main() {
	_window_size(1000, 1000);		//Only Quads?? Why?? Needs a fix!
	_map = sur::Initialize();
	_Amap(_map, _window_size);
	Window();
	sur::Render render(Color(85, 107, 47));
	render.FPS();
	sur::LoadObj a("C:\\Users\\gero\\Desktop\\Hardcore Engine\\Hgineres\\Tree.Hgineres", { 0,0 });
	for(;;) {
		render.ClearScreenBuffer();	
		a.Bind();
		render.RenderScreenBuffer();
	}
}
