

#pragma once

#include "../../../Includes.h"

namespace sur
{
	 struct Input {
		struct Mouse {

			static Vec2f Position();
			static bool LClick();
			static bool RClick();

		};
		struct Keyboard {


		};
	};
}