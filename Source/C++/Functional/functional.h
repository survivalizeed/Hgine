

#pragma once
#include "includes.h"

extern sur::Map_Analyses _Amap;

namespace sur {

	sur::Maps Initialize();

	//Unused
	i32 CharCounter(char Char, const std::string& Data);

	/*
	Play a sound. Currently there are only .wav files supported
	The volume is represented in hex. The max volume is 0xFFFFFFFF.
	The first 4 digits(FFFF) are the volume for your left box and
	the last 4 digits are the volume for your right box.
	*/
	void Sound(const char* path, u32 params, i32 volume);

	//Not thaaaat fast :)
	i32 RandomRange(i32 min, i32 max);

	//Cast the object to a (sur::Master*). Make sure it inheritates from the Master class
	void MoveTowards(Master* const current, Master* const target, f32 speed, const Axis& axis, bool detect);

	//To wait one second, just store the value of the first call and compare in an if, if it is value + 1000.
	i64 GetMilliseconds();

	inline void SetPixel(Vec2 position, Color color, i32 CollisionId = 0, i32 TriggerId = 0) {
		_Amap.Render(position, color);
		if (CollisionId != 0)
			_Amap.Collider(position, CollisionId);
		if(CollisionId != 0)
			_Amap.Trigger(position, TriggerId);
	}

	template<Axis axis>
	auto Distance(Master* const a, Master* const b) {
		assert(a->GetName() == "invalid" || b->GetName() == "invalid", 999999999);
		if constexpr (axis == Axis::X) {
			return abs(a->GetPosition().x - b->GetPosition().x);
		}
		else if (axis == Axis::Y) {
			return abs(a->GetPosition().y - b->GetPosition().y);
		} 
		if constexpr (axis == Axis::Both) {
			return Vec2(a->GetPosition() - b->GetPosition()).absolute();
		}
	}

	
}