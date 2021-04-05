

#include "functional.h"

extern sur::Map_Analyses _Amap;
extern sur::Vec2 _window_size;

sur::Maps sur::Initialize()
{
	eassert(_window_size.x == 0 || _window_size.y == 0, "_window_size not initialized");
	return { new i32[_window_size.x * _window_size.y],new i32[_window_size.x * _window_size.y], 
	new DWORD[_window_size.x * _window_size.y] };
}


i32 sur::CharCounter(char Char, const std::string& Data) {
	i32 counter = 0;
	for (i32 i = 0; i < Data.size(); i++) {
		if (Data[i] == Char) {
			counter++;
		}
	}
	return counter;
}

inline void sur::Sound(const char* path, u32 params, i32 volume)
{
	waveOutSetVolume(NULL, volume);
	PlaySoundA(path, NULL, params);
}

inline i32 sur::RandomRange(i32 min, i32 max)
{
	return rand() % (max - min + 1) + min;
}

void sur::MoveTowards(sur::Master* current, sur::Master* target, const sur::Vec2f& speed, bool detect)	// 1 = true(move), 0 = false(don't move)
{
	//assert(target->GetName() == "invalid" || current->GetName() == "invalid");
	if (current->GetPosition().x < target->GetPosition().x) {	// positive x
		if (current->GetPosition().x != target->GetPosition().x)
			current->Move({ speed.x,0 },detect);
	}
	if (current->GetPosition().x > target->GetPosition().x) { // negative x
		if (current->GetPosition().x != target->GetPosition().x)
			current->Move({ -speed.x,0 }, detect);
	}
	if (current->GetPosition().y < target->GetPosition().y) {	// positive y
		if (current->GetPosition().y != target->GetPosition().y)
			current->Move({ 0,-speed.y }, detect);
	}
	if (current->GetPosition().y > target->GetPosition().y) { // negative y
		if (current->GetPosition().y != target->GetPosition().y)
			current->Move({ 0,speed.y }, detect);
	}
}

i64 sur::GetMilliseconds()
{
	using namespace std::chrono;
	return (i64)duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

u32 sur::Distance(sur::Master* a, sur::Master* b, bool xAxis)
{
	assert(a->GetName() == "invalid" || b->GetName() == "invalid",999999999);
	if(xAxis)
		return abs(a->GetPosition().x - b->GetPosition().x);
	return abs(a->GetPosition().y - b->GetPosition().y);
}

void sur::Freeze(bool freeze)
{

}

