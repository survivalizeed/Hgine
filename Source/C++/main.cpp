#include "../C++/Functional/includes.h"
#include "../C++/Functional/functional.h"
#include "../C++/Functional/TemporaryObjects.h"


extern lua_State* Start();
extern sur::Map_Analyses _Amap;
extern sur::Input _input;
using namespace sur::Instancer;

int main() {

	lua_State* LC = Start();
	sur::Render renderer(Color(0, 0, 0), true, 0.4f, false);
	renderer.DebugConsole(_debug);
	renderer.FPS();

	//sur::Object player(_resource_path + "player.Hgineres", { 0,0 }, "obj", 1);
	//sur::Cuboid c(Vec3f(0, 0, 50), Vec3f(100, 0, 50), Vec3f(100, 100, 50), Vec3f(0, 100, 50),
	//Vec3f(0, 0, 150), Vec3f(100, 0, 150), Vec3f(100, 100, 150), Vec3f(0, 100, 150), Color(255, 0, 0),
	//Vec3f(0, 0, 50));

	sur::Mesh c("C:\\Users\\gero\\Desktop\\gun.obj", { 0,0,0 }, Color(255, 255, 255), { 200,200,200 });
	f32 angleX = 0;
	f32 angleY = 0;
	f32 angleZ = 0;
	for (;;) {
		renderer.ClearScreenBuffer();
		c.Bind(true, 300);
		if (_input.keyboard.Key(Keys::J)) {
			c.Rotate(Dimension::X, (i32)angleX);
			angleX += 0.2f;
		}
		if (_input.keyboard.Key(Keys::K)) {
			c.Rotate(Dimension::Y, (i32)angleY);
			angleY += 0.2f;
		}
		if (_input.keyboard.Key(Keys::L)) {
			c.Rotate(Dimension::Z, (i32)angleZ);
			angleZ += 0.2f;
		}
		if (_input.keyboard.Key(Keys::W))
			c.Move({ 0,0,1 });
		if (_input.keyboard.Key(Keys::S))
			c.Move({ 0,0,-1 });
		if (_input.keyboard.Key(Keys::D))
			c.Move({ 1,0,0 });
		if (_input.keyboard.Key(Keys::A))
			c.Move({ -1,0,0 });
		renderer.RenderScreenBuffer();	
	}
}
//player.Bind(true, ColliderType::Exact);
//if (_input.keyboard.Key(Keys::A))
//	player.Move({ -1,0 }, 0,true);
//if (_input.keyboard.Key(Keys::D))
//	player.Move({ 1,0 }, 0, true);


//sur::Light light1 ({ 0,0 }, 500, Color(200, 200, 0), "light");
//if(_input.mouse.RClick())
//	light1.SetPosition(_input.mouse.Position());

		//c.Bind(true, 120);
		//c.Rotate(Dimension::X, (i32)angle);
		//c.Rotate(Dimension::Y, (i32)angle);
		//c.Rotate(Dimension::Z, (i32)angle);
		//if (_input.keyboard.Key(Keys::W)) {
		//	c.Move({ 0,0,1 });
		//}
		//if (_input.keyboard.Key(Keys::S)) {
		//	c.Move({ 0,0,-1 });
		//}
		//if (_input.keyboard.Key(Keys::D)) {
		//	c.Move({ 1,0,0 });
		//}
		//if (_input.keyboard.Key(Keys::A)) {
		//	c.Move({ -1,0,0 });
		//}
		//if (_input.keyboard.Key(Keys::Q)) {
		//	c.Move({ 0,-1,0 });
		//}
		//if (_input.keyboard.Key(Keys::E)) {
		//	c.Move({ 0,1,0 });
		//}