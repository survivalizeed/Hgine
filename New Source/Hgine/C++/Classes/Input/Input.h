

#pragma once

#include "../../../Includes.h"

namespace sur
{

    enum Key : u32
    { //	<- No enum class because otherwise GetAsyncKeyState wouldn't be able to read the key

        None = 0,
        A = 0x41,
        B = 0x42,
        C = 0x43,
        D = 0x44,
        E = 0x45,
        F = 0x46,
        G = 0x47,
        H = 0x48,
        I = 0x49,
        J = 0x4A,
        K = 0x4B,
        L = 0x4C,
        M = 0x4D,
        N = 0x4E,
        O = 0x4F,
        P = 0x50,
        Q = 0x51,
        R = 0x52,
        S = 0x53,
        T = 0x54,
        U = 0x55,
        V = 0x56,
        W = 0x57,
        X = 0x58,
        Y = 0x59,
        Z = 0x5A,
        N0 = 0x30,
        N1 = 0x31,
        N2 = 0x32,
        N3 = 0x33,
        N4 = 0x34,
        N5 = 0x35,
        N6 = 0x36,
        N7 = 0x37,
        N8 = 0x38,
        N9 = 0x39,
        Num0 = 0x60,
        Num1 = 0x61,
        Num2 = 0x62,
        Num3 = 0x63,
        Num4 = 0x64,
        Num5 = 0x65,
        Num6 = 0x66,
        Num7 = 0x67,
        Num8 = 0x68,
        Num9 = 0x69,
        Space = 0x20,        
        ArLeft = 0x25,
        ArUp = 0x26,
        ArRight = 0x27,
        ArDown = 0x28,
        Escape = 0x1B,
        Enter = 0x0D,
        Shift = 0x10,
        Control = 0x11,
        Back = 0x08
    };

	 struct Input {

		struct Mouse {

			static std::optional<Vec2f> Position();
			static bool LClick();
			static bool RClick();

		};

		struct Keyboard {
			
			static bool KeyHeld(Key key);
			static bool KeyPress(Key key);

		private:

			inline static Key charPressed[26] = { None }; 
            inline static Key numericePressed[10] = { None };
            inline static Key numNumericePressed[10] = { None };
            inline static Key miscPressed[10] = { None };

		};

	 };
}