

#include "includes.h"

extern void Window(const char* name,int params);
extern sur::Map_Analyses _Amap;
extern sur::Input _input;

using sur::Instancer::Types;

int main() {
	_debug = false;
	_window_size(750, 750);		//Only Quads?? Why?? Needs a fix!
	_map = sur::Initialize();
	_Amap(_map, _window_size);
	
	Window("Fuck Adrian", WS_BORDER | WS_SYSMENU | WS_CAPTION);
	
	sur::Render renderer(Color(100, 107, 47));
	renderer.FPS();
	renderer.DebugConsole(true);

	sur::Instancer::Add(new sur::LoadObj("C:\\Users\\...\\Desktop\\Hardcore Engine\\Hgineres\\Human.Hgineres", { 100, 100 }, "shot", 50),Types::Obj);
	for(;;) {
		renderer.ClearScreenBuffer();	
		sur::Instancer::GetObj("shot")->Bind(true, ColliderType::Static);
		if (_input.mouse.LClick()) {
			if (_Amap.Collider(_input.mouse.Position().x, _input.mouse.Position().y) == sur::Instancer::GetObj("shot")->id) {
				sur::Instancer::GetObj("shot")->SetPos({ sur::RandomRange(0,_window_size.x - sur::Instancer::GetObj("shot")->GetSize().x), sur::RandomRange(0,_window_size.y - sur::Instancer::GetObj("shot")->GetSize().y) });
			}
		}
		renderer.RenderScreenBuffer();
	}
}

