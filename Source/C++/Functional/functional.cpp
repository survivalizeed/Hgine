

#include "functional.h"


extern sur::Map_Analyses _Amap;
extern sur::Vec2 _window_size;

sur::Maps sur::Initialize()
{
	if (_window_size.x == 0 || _window_size.y == 0) {
		Error("_window_size not initialized");
	}
	return { new int[_window_size.x * _window_size.y],new int[_window_size.x * _window_size.y], 
	new DWORD[_window_size.x * _window_size.y] };
}


int sur::CharCounter(char Char, const std::string& Data) {
	int counter = 0;
	for (int i = 0; i < Data.size(); i++) {
		if (Data[i] == Char) {
			counter++;
		}
	}
	return counter;
}

void sur::Sound(const char* path, unsigned int params)
{
	PlaySoundA(path, NULL, params);
}

int sur::RandomRange(int min, int max)
{
	return  rand() % (max - min + 1) + min;
}

void sur::MoveTowards(sur::Master* current, sur::Master* target, const sur::Vec2& axis, bool detect)	// 1 = true(move), 0 = false(don't move)
{
	if (current->GetPosition().x < target->GetPosition().x) {	// positive x
		if (current->GetPosition().x != target->GetPosition().x)
			current->Move({ axis.x,0 },detect);
	}
	if (current->GetPosition().x > target->GetPosition().x) { // negative x
		if (current->GetPosition().x != target->GetPosition().x)
			current->Move({ -axis.x,0 }, detect);
	}
	if (current->GetPosition().y < target->GetPosition().y) {	// positive y
		if (current->GetPosition().y != target->GetPosition().y)
			current->Move({ 0,-axis.y }, detect);
	}
	if (current->GetPosition().y > target->GetPosition().y) { // negative y
		if (current->GetPosition().y != target->GetPosition().y)
			current->Move({ 0,axis.y }, detect);
	}
}
