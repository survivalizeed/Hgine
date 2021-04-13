

#include "functional.h"

extern sur::Vec2 _window_size;
extern std::vector<i32> identitys;
extern std::vector<void*> ptrs;

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

void sur::Sound(const char* path, u32 params, i32 volume)
{
	waveOutSetVolume(NULL, volume);
	PlaySoundA(path, NULL, params);
}

i32 sur::RandomRange(i32 min, i32 max)
{
	return rand() % (max - min + 1) + min;
}

void sur::MoveTowards(Master* current, Master* target, f32 speed, const Axis& axis, bool detect)
{
	assert(target->GetName() == "invalid" || current->GetName() == "invalid");
	Vec2f direction(target->GetPosition() - current->GetPosition());
	switch (axis){
	case Axis::X: direction.y = 1; break;
	case Axis::Y: direction.x = 1; break;
	default: break;}
	direction.normalize();
	switch (axis) {
	case Axis::X: direction.y = 0; break;
	case Axis::Y: direction.x = 0; break;
	default: break;
	}
	current->Move(direction * speed, detect);
}

i64 sur::GetMilliseconds()
{
	using namespace std::chrono;
	return (i64)duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}



