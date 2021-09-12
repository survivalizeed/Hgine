

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
			
			static bool KeyHeld(Keys::Keys key);
			static bool KeyPress(Keys::Keys key);

		private:

			inline static Keys::Keys pressed[27] = { Keys::Keys::None }; // 27 because of the SPACE key

		};

	 };
}