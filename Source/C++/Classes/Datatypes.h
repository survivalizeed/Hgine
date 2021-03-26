

#pragma once

#include "../Functional/includes.h"

typedef int8_t i8;
typedef	int16_t i16;
typedef int i32;
typedef	long int i64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef	unsigned int u32;
typedef unsigned long int u64;

typedef Gdiplus::Color Color;

typedef const int size;

constexpr int Second = 1000;
constexpr int Minute = 60000;

namespace sur {
	//
	// struct 
	//
	//
	// Vec2 -> i32
	//
	struct Vec2 {

		i32 x, y;
		
		Vec2() { x = 0; y = 0; }

		Vec2(i32 x, i32 y)	: x(x), y(y){}
		
		Vec2(const Vec2& vector2d)	: x(vector2d.x), y(vector2d.y)	{}

		inline void operator ()(i32 x, i32 y) {this->x = x;this->y = y;}
		
		inline void operator ()(const Vec2& vector2d) {x = vector2d.x; y = vector2d.y;}
		
		inline Vec2 invert() {
			return { this->x * -1, this->y * -1 };
		}
		inline float magnitude() {
			return (float)sqrt(pow(x, 2) + pow(y, 2));
		}

		inline void operator =(const Vec2& vector2d) { x = vector2d.x; y = vector2d.y; }

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
		inline friend Vec2 operator --(const Vec2& first) {
			return { first.x - 1, first.y - 1 };
		}
		inline friend Vec2 operator ++(const Vec2& first) {
			return { first.x + 1, first.y + 1 };
		}
		inline friend bool operator ==(const Vec2& first, const Vec2& second) {
			return (first.x == second.x && first.y == second.y) ? true : false;
		}
		inline friend bool operator >(Vec2 first, Vec2 second) {
			return (first.magnitude() > second.magnitude()) ? true : false;
		}
		inline friend bool operator >=(Vec2 first, Vec2 second) {
			return (first.magnitude() >= second.magnitude()) ? true : false;
		}
		inline friend bool operator <(Vec2 first, Vec2 second) {
			return (first.magnitude() < second.magnitude()) ? true : false;
		}
		inline friend bool operator <=(Vec2 first, Vec2 second) {
			return (first.magnitude() <= second.magnitude()) ? true : false;
		}
		friend std::ostream& operator<<(std::ostream& os, const Vec2& vector2d) {
			os << "X: " << vector2d.x << " Y: " << vector2d.y;
			return os;
		}
	};
	//
	// Map poi32er for Rendering, Collision and Trigger detection
	//
	struct Maps {
		i32* ColliderMap, * TriggerMap;
		DWORD* RenderMap;
	};
}
//
// enum
//

// Input
enum Keys : u32{	//	<- No enum class because otherwise GetAsyncKeyState would't be able to read the key
	A = 0x41, B = 0x42, C = 0x43, D = 0x44, E = 0x45, F = 0x46, G = 0x47, H = 0x48, I = 0x49, J = 0x4A,
	K = 0x4B, L = 0x4C, M = 0x4D, N = 0x4E, O = 0x4F, P = 0x50, Q = 0x51, R = 0x52, S = 0x53, T = 0x54,
	U = 0x55, V = 0x56, W = 0x57, X = 0x58, Y = 0x59, Z = 0x5A, SPACE = 0x20
};

// Colliders
enum class ColliderType {
	Static, Filled, Outline, None
};

// Template stuff
template <typename CallBackType>
using cb_ptr = void(*)(CallBackType);

template <typename T>
inline constexpr bool is_Vec2 = std::_Is_any_of_v<std::remove_cv_t<T>, sur::Vec2>;

template <typename T>
concept VEC = is_Vec2<T>;	// Made with a concept because the variadic functionality is only availabe in templates 
