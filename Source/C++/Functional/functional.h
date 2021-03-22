

#pragma once
#include "includes.h"


namespace sur {

	sur::Maps Initialize();

	int CharCounter(char Char, const std::string& Data);

	void Sound(const char* path, unsigned int params);

	int RandomRange(int min, int max);

	//Cast the object to a (sur::Master*). Make sure it inheritates from the Master class
	void MoveTowards(sur::Master* const current, sur::Master* const target, const sur::Vec2& axis, bool detect);

}