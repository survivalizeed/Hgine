

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
			
			static bool KeyHeld(Keys key);
			static bool KeyPress(Keys key);

		private:

			inline static Keys pressed[27] = { Keys::None }; // 27 because of the SPACE key

		};

	 };
}