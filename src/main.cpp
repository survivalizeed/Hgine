

#include "includes.h"

extern void Window(const char* name,int params);
extern sur::Map_Analyses _Amap;
extern sur::Input _input;


void Callbacka(sur::Master* obj) {
	l("CallbackA: " << obj->GetName());
}

void Callbackb(sur::Master* obj) {	
	l("CallbackB: "<< obj->GetName());
}

int main() {
	_debug = false;
	_window_size(750, 750);		//Only Quads?? Why?? Needs a fix!
	_map = sur::Initialize();
	_Amap(_map, _window_size);
	Window("Fuck Adrian", WS_BORDER | WS_SYSMENU | WS_CAPTION);
	sur::Render render(Color(100, 107, 47));
	render.FPS();
	render.DebugConsole(false);
	sur::LoadObj a("C:\\Users\\gero\\Desktop\\Hardcore Engine\\Hgineres\\Shot.Hgineres", { 100, 100 },"OBJ", 50);
	for(;;) {
		render.ClearScreenBuffer();	
		a.Bind(true, ColliderType::Outline);
		if (_input.mouse.LClick()) {
			if (_Amap.Collider(_input.mouse.Position().x, _input.mouse.Position().y) == a.id) {
				a.SetPos({ sur::RandomRange(0,_window_size.x - a.GetSize().x), sur::RandomRange(0,_window_size.y - a.GetSize().y) });		
			}
		}
		render.RenderScreenBuffer();
	}
}

