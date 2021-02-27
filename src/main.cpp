

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
	Debug = true;
	_window_size(750, 750);		//Only Quads?? Why?? Needs a fix!
	_map = sur::Initialize();
	_Amap(_map, _window_size);
	Window("Demo", WS_BORDER | WS_SYSMENU | WS_CAPTION);
	sur::Render render(Color(100, 107, 47));
	render.FPS();
	sur::LoadObj a("C:\\Users\\gero\\Desktop\\Hardcore Engine\\Hgineres\\Human.Hgineres", { 0, 350 },"OBJ", 50);
	sur::Rectangle b({ 500,400 }, { 50,50 }, Color(255, 100, 100), "B",13);
	for(;;) {
		render.ClearScreenBuffer();	
		a.Bind(true,ColliderType::Outline);
		b.Bind(true);
		if (_input.keyboard.Key(W))
			a.Move({ 0,2 });
		if (_input.keyboard.Key(A))
			a.Move({ -2,0 });
		if (_input.keyboard.Key(S))
			a.Move({ 0,-2 });
		if (_input.keyboard.Key(D))
			a.Move({ 2,0 });
		//if (_input.keyboard.Key(Keys::F))
		//	a.Move({ 1,0 });
		//if (_input.keyboard.Key(Keys::Q))
		//	a.Move({ -1,0 });
		if (_input.mouse.RClick()) {
			system("CLS");
			l(_Amap.Collider(_input.mouse.Position().x, _input.mouse.Position().y));
		}

		render.RenderScreenBuffer();
	}
}

