#include "../C++/Functional/includes.h"
#include "../C++/Functional/functional.h"
#include "../C++/Functional/TemporaryObjects.h"

extern lua_State* Start();
extern sur::Map_Analyses _Amap;
extern sur::Input _input;
using namespace sur::Instancer;


int main() {
	
	lua_State* LC = Start();
	sur::Render renderer(Color(0, 0, 0), true);
	renderer.DebugConsole(_debug);
	renderer.FPS();

	i32 r = 0;
	i32 g = 0;
	i32 b = 0;

	sur::Object obj((_resource_path + "woods.hgineres").c_str(), { 0,0 }, "obj", 1);
	sur::Light light({ 5,5 }, 3.f, Color(40, 0, 0), "light");
	sur::Light light2({ 5,5 }, 3.f, Color(0, 40, 0), "light2");

	for (;;) {
		renderer.ClearScreenBuffer();
		obj.Bind(true, ColliderType::None);
		
		if (_input.mouse.RClick()) {
			light.SetPosition(_input.mouse.Position());
		}
		if (_input.mouse.LClick()) {
			light2.SetPosition(_input.mouse.Position());
		}
		renderer.RenderScreenBuffer();
	}
}