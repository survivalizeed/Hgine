

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
	
	sur::Render renderer(Color(100, 107, 47),1);
	renderer.FPS();
	renderer.DebugConsole(true);

	sur::Instancer::Add(new sur::LoadObj("C:\\Users\\gero\\Desktop\\Hardcore Engine\\Hgineres\\Human.Hgineres", { 0, 0 }, "shot", 50),Types::Obj);
	sur::Instancer::Add(new sur::LoadObj("C:\\Users\\gero\\Desktop\\Hardcore Engine\\Hgineres\\Human.Hgineres", { 200, 200 }, "shot2", 51), Types::Obj);
	sur::Instancer::Add(new sur::LoadObj("C:\\Users\\gero\\Desktop\\Hardcore Engine\\Hgineres\\Human.Hgineres", { 100, 500 }, "shot3", 52), Types::Obj);
	sur::Instancer::Add(new sur::LoadObj("C:\\Users\\gero\\Desktop\\Hardcore Engine\\Hgineres\\Human.Hgineres", { 100, 300 }, "shot4", 53), Types::Obj);
	for (;;) {
		renderer.ClearScreenBuffer();
		sur::Instancer::GetObj("shot")->Bind(true, ColliderType::Outline);
		sur::Instancer::GetObj("shot2")->Bind(true, ColliderType::Outline);
		sur::Instancer::GetObj("shot3")->Bind(true, ColliderType::Outline);
		sur::Instancer::GetObj("shot4")->Bind(true, ColliderType::Outline);
		if (_input.keyboard.Key(Keys::W))
			sur::Camera::Move({ 0,10 });
		if (_input.keyboard.Key(Keys::A))
			sur::Camera::Move({ -10,0 });
		if (_input.keyboard.Key(Keys::S))
			sur::Camera::Move({ 0,-10 });
		if (_input.keyboard.Key(Keys::D))
			sur::Camera::Move({ 10,0 });
		renderer.RenderScreenBuffer();
	}
}

