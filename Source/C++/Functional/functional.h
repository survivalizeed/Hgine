

#pragma once

#include "includes.h"


namespace sur {
	sur::Maps Initialize();

	int CharCounter(char Char, std::string Data);

	void Sound(const char* path, unsigned int params);

	int RandomRange(int min, int max);

}



