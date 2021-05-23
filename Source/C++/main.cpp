#include "Functional/includes.h"
#include "Functional/functional.h"
#include "Functional/TemporaryObjects.h"

extern lua_State* Start();
extern sur::Map_Analyses _Amap;
extern sur::Input _input;
using sur::Instancer::Types;

int main() {
	lua_State* LC = Start();
	
	sur::Render renderer(Color(0, 0, 0), true, 0);
	renderer.DebugConsole(_debug);
	renderer.FPS();
	
	sur::Rectangle rect1({ 0,0 }, { 1,1 }, Color(0, 0, 255), "rect1", 1, false, { 0 });
	sur::Rectangle rect2({ -1,-1 }, { 0 - Unit(5),0 - Unit(5) }, Color(0, 255, 0), "rect2", 2, false, { 0 });

	for (;;) {
		renderer.ClearScreenBuffer();
		rect1.Bind(true, true);
		rect2.Bind(true, true);

		if (_input.keyboard.Key(Keys::W))
			rect1.Move({ 0,1 }, true);
		if (_input.keyboard.Key(Keys::A))
			rect1.Move({ -1,0 }, true);
		if (_input.keyboard.Key(Keys::S))
			rect1.Move({ 0,-1 }, true);
		if (_input.keyboard.Key(Keys::D))
			rect1.Move({ 1,0 }, true);

		renderer.RenderScreenBuffer();
	}
}

