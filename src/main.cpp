

#include "includes.h"

extern void Window(const char* name,int params);
extern sur::Map_Analyses _Amap;
extern sur::Input _input;

void Callbacka(sur::Master* obj) {
	l("CallbackA: " << obj->GetName());
}

void Callbackb(sur::Master* obj) {
	
	l("CallbackB: "<<obj->GetName());
}

int main() {
	_window_size(1000, 1000);		//Only Quads?? Why?? Needs a fix!
	_map = sur::Initialize();
	_Amap(_map, _window_size);
	Window("Demo",WS_BORDER | WS_SYSMENU | WS_CAPTION);
	sur::Render render(Color(85, 107, 47));
	render.FPS();
	//sur::LoadObj a("C:\\Users\\gero\\Desktop\\Hardcore Engine\\Hgineres\\Tree.Hgineres", { 0,0 });
	sur::Rectangle a({ -100,1 }, { 200,200 }, Color(100, 255, 100), "A", 12);
	sur::Rectangle b({ 400,400 }, { 50,50 }, Color(255, 100, 100), "B",12);
	a.callback = Callbacka;
	b.callback = Callbackb;
	for(;;) {
		render.ClearScreenBuffer();	
		a.Bind(true);
		b.Bind(true);
		if (_input.keyboard.Key(sur::W))
			a.Move({ 0,1 });
		if (_input.keyboard.Key(sur::A))
			a.Move({ -1,0 });
		if (_input.keyboard.Key(sur::S))
			a.Move({ 0,-1 });
		if (_input.keyboard.Key(sur::D))
			a.Move({ 1,0 });
		render.RenderScreenBuffer();
	}
}

