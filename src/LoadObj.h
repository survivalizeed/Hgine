

#pragma once

#include "includes.h"

namespace sur {
	class LoadObj
	{
	private:
		int x = 0;
		int y = 0;
		int MaxXvalue;
		const char* Path;
		sur::Vec2 position;

		std::vector<int> YCoords;
		std::vector<int> XCoords;
		std::vector<Gdiplus::Color> Colors;
		std::vector<int>* MaxX = new std::vector<int>;

		void Load();

	public:
		LoadObj(const char* Path, sur::Vec2 position) : Path(Path), position(position) { Load(); }

		void operator()(const char* Path, sur::Vec2 position) {
			this->Path = Path;
			this->position = position;
			Load();
		}

		void Bind();

		void Move(sur::Vec2 direction);

	};
}
