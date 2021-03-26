

#pragma once
#include "includes.h"


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

	inline i32 RandomRange(i32 min, i32 max);

	//Cast the object to a (sur::Master*). Make sure it inheritates from the Master class
	void MoveTowards(sur::Master* const current, sur::Master* const target, const sur::Vec2& speed, bool detect);

	//To wait one second, just store the value of the first call and compare in an if, if it is value + 1000.
	i64 GetMilliseconds();

	u32 Distance(sur::Master* a, sur::Master* b, bool xAxis);
}