#include "../C++/Functional/includes.h"
#include "../C++/Functional/functional.h"
#include "../C++/Functional/TemporaryObjects.h"
#include "Game.h"

extern lua_State* Start();
extern sur::Map_Analyses _Amap;
extern sur::Input _input;


extern void Splash(sur::Render& renderer);
extern void Menu(sur::Render& renderer);
extern void Level1(sur::Render& renderer);


int main() {
	lua_State* LC = Start();
	sur::Render renderer(Color(0, 0, 0), false, 1.f, false);
	renderer.DebugConsole(_debug);
	renderer.FPS();
	
	//Splash(renderer);
	//Menu(renderer);
	Level1(renderer);
	
	sur::Instancer::ClearAll();
}

