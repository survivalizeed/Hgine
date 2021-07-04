#include "../C++/Functional/includes.h"
#include "../C++/Functional/functional.h"
#include "../C++/Functional/TemporaryObjects.h"

extern lua_State* Start();
extern sur::Map_Analyses _Amap;
extern sur::Input _input;
using namespace sur::Instancer;


int main() {

	lua_State* LC = Start();
	sur::Render renderer(Color(0, 0, 0), true, 0.4f,true);
	renderer.DebugConsole(_debug);
	renderer.FPS();

	i32 r = 0;
	i32 g = 0;
	i32 b = 0;

	sur::Object wood((_resource_path + "woods.Hgineres").c_str(), { 0,0 }, "obj", 1);
	

	sur::Light light({ 5,5 }, 3.f, Color(0,0,200), "light");

	for (;;) {
		renderer.ClearScreenBuffer();
		wood.Bind(true, ColliderType::None);
		 
		if (_input.mouse.RClick()) {
			light.SetPosition(_input.mouse.Position());
		}
		renderer.RenderScreenBuffer();
	}
}