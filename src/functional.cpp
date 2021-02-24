

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

int sur::CharCounter(char Char, std::string Data) {
	int counter = 0;
	for (int i = 0; i < Data.size(); i++) {
		if (Data[i] == Char) {
			counter++;
		}
	}
	return counter;
}
