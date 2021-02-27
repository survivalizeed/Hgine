

#pragma once

#include "includes.h"

typedef int8_t int8;
typedef	int16_t int16;
typedef int int32;
typedef	long int int64;

typedef Gdiplus::Color Color;

typedef const int size;

template <typename CallBackType>
using cb_ptr = void(*)(CallBackType);

namespace sur {
	//
	// struct 
	//
	struct Vec2 {	
		int x, y;
		
		Vec2() { x = 0; y = 0; }

		Vec2(int x, int y) : x(x), y(y){}
		inline float magnitude() {
			return (float)sqrt(pow(x,2) + pow(y,2));
		}
		
		inline void operator ()(int x, int y) {this->x = x;this->y = y;}
		
		inline void operator ()(const Vec2& vector2d) {x = vector2d.x; y = vector2d.y;}
		
		inline friend Vec2 operator +(const Vec2& first, const Vec2& second) {
			return { first.x + second.x, first.y + second.y };
		}
		inline friend Vec2 operator -(const Vec2& first, const Vec2& second) {
			return { first.x - second.x, first.y - second.y };
		}
		inline friend Vec2 operator *(const Vec2& first, const Vec2& second) {
			return { first.x * second.x, first.y * second.y };
		}
		inline friend Vec2 operator /(const Vec2& first, const Vec2& second) {
			if (second.x == 0 || second.y == 0) {
				Error("Dividing by zero not allowed");
			}
			return { first.x / second.x, first.y / second.y };
		}
	};
	//
	// struct <- should be in the classes.h
	//
	struct Maps {
		int* ColliderMap, * TriggerMap;
		DWORD* RenderMap;
	};
}
//
// enum
//

// Input
enum Keys : unsigned int{	//	<- No enum class because otherwise GetAsyncKeyState would't be able to read the key
	A = 0x41, B = 0x42, C = 0x43, D = 0x44, E = 0x45, F = 0x46, G = 0x47, H = 0x48, I = 0x49, J = 0x4A,
	K = 0x4B, L = 0x4C, M = 0x4D, N = 0x4E, O = 0x4F, P = 0x50, Q = 0x51, R = 0x52, S = 0x53, T = 0x54,
	U = 0x55, V = 0x56, W = 0x57, X = 0x58, Y = 0x59, Z = 0x5A
};

// Colliders
enum class ColliderType {
	Static, Filled, Outline
};


