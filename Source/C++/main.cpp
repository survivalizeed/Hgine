#include "../C++/Functional/includes.h"
#include "../C++/Functional/functional.h"
#include "../C++/Functional/TemporaryObjects.h"

extern lua_State* Start();
extern sur::Map_Analyses _Amap;
extern sur::Input _input;
using namespace sur::Instancer;


int main() {

	lua_State* LC = Start();
	sur::Render renderer(Color(0, 0, 0), true, 0.4f,false);
	renderer.DebugConsole(_debug);
	renderer.FPS();


	sur::Object wood((_resource_path + "player.Hgineres").c_str(), { 0,0 }, "obj", 1);
	

	for (;;) {
		renderer.ClearScreenBuffer();
		wood.SetPosition(wood.GetPosition());
		wood.Bind(true, ColliderType::None);
		if (_input.keyboard.Key(Keys::A))
			l(wood.Move({ -1,0 }, true));
		if (_input.keyboard.Key(Keys::D))
			l(wood.Move({ 1,0 }, true));
		
		renderer.RenderScreenBuffer();
	}
}