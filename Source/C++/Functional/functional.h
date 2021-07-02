

#pragma once

#include "includes.h"

extern sur::Map_Analyses _Amap;

namespace sur {

	sur::Maps Initialize();

	//Unused
	i32 CharCounter(char Char, std::string_view Data);

	/*
	Play a sound. Currently there are only .wav files supported
	The volume is represented in hex. The max volume is 0xFFFFFFFF.
	The first 4 digits(FFFF) are the volume for your left box and
	the last 4 digits are the volume for your right box.
	*/
	void Sound(const std::string& path, u32 params, i32 volume);

	//Not thaaaat fast :)
	i32 RandomRange(i32 min, i32 max);

	//Cast the object to a (sur::Master*). Make sure it inheritates from the Master class
	void MoveTowards(Master* const current, Master* const target, f32 speed, const Axis& axis, bool detect);

	Vec2f Direction(Vec2f first, Vec2f second);

	//To wait one second, just store the value of the first call and compare in an if, if it is value + 1000.
	i64 GetMilliseconds();

	Vec3f RotateX(Vec3f vec, Vec3f origin, i32 angle);

	Vec3f RotateY(Vec3f vec, Vec3f origin, i32 angle);

	Vec3f RotateZ(Vec3f vec, Vec3f origin, i32 angle);

	void SetPixel(Vec2f position, Color color, i32 CollisionId = 0, i32 TriggerId = 0);

	Vec2f Absolute(Vec2f vec);

	template<Axis axis>
	auto Distance(const Master* const a, const Master* const b) {
		assert(a->GetName() == "invalid" || b->GetName() == "invalid", 999999999);
		if constexpr (axis == Axis::X) {
			return abs(a->GetPosition().x - b->GetPosition().x);
		}
		else if (axis == Axis::Y) {
			return abs(a->GetPosition().y - b->GetPosition().y);
		} 
		if constexpr (axis == Axis::Both) {
			return Vec2f(a->GetPosition() - b->GetPosition()).absolute();
		}
	}

	
}