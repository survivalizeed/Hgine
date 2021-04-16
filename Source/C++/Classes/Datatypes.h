

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

typedef float f32;
typedef double f64;

typedef DWORD Color;

typedef const int size;

constexpr int Second = 1000;
constexpr int Minute = 60000;
constexpr f32 PI = 3.1415926f;

namespace sur {
	//
	// struct 
	//
	//
	// Vec2 -> i32
	//
	struct Vec2f {
		f32 x, y;


		Vec2f() = default;

		Vec2f(f32 x, f32 y) : x(x), y(y) {}

		Vec2f(const Vec2f& vector2d) : x(vector2d.x), y(vector2d.y) {}

		inline f32 magnitude() { return (f32)sqrt(pow(x, 2) + pow(y, 2)); }
		inline void invert() { x *= -1.f; y *= -1.f; }
		inline void normalize() { float mag = magnitude();  x /= mag; y /= mag; }

		inline void operator ()(f32 x, f32 y) { this->x = x; this->y = y; }
		inline void operator ()(const Vec2f& vector2d) { x = vector2d.x; y = vector2d.y; }
		inline void operator =(const Vec2f& vector2d) { x = vector2d.x; y = vector2d.y; }

		inline Vec2f operator +(const Vec2f& other) const { return { x + other.x, y + other.y }; }
		inline Vec2f operator -(const Vec2f& other) const { return { x - other.x, y - other.y }; }
		inline Vec2f operator *(f32 value) const { return{ x * value, y * value }; }

		friend std::ostream& operator<<(std::ostream& os, const Vec2f& vector2d) {
			os << "X: " << vector2d.x << " Y: " << vector2d.y;
			return os;
		}
	};

	struct Vec2 {

		i32 x = 0, y = 0;

		Vec2() = default;

		Vec2(i32 x, i32 y) : x(x), y(y) {}

		Vec2(const Vec2& vector2d) : x(vector2d.x), y(vector2d.y) {}

		inline void invert() { x *= -1; y *= -1; }
		inline f32 magnitude() { return (f32)sqrt(pow(x, 2) + pow(y, 2)); }
		inline void absolute() { (void)abs(x); (void)abs(y); }
		inline f32 angleToXaxis() {
			if (y >= 0)
				return acos(x / magnitude());
			else
				return acos(x / magnitude());
		}
		
		inline void operator ()(i32 x, i32 y) { this->x = x; this->y = y; }
		inline void operator ()(const Vec2& vector2d) { x = vector2d.x; y = vector2d.y; }
		inline void operator =(const Vec2& vector2d) { x = vector2d.x; y = vector2d.y; }	
	
		inline Vec2 operator +(const Vec2& other) const { return { x + other.x, y + other.y }; }
		inline Vec2 operator -(const Vec2& other) const { return { x - other.x, y - other.y }; }
		inline int operator *(const Vec2& other) const { return x * other.x + y * other.y; }
		inline Vec2 operator /(const Vec2& other) const { return { x / other.x, y / other.y }; }		
		
		inline Vec2 operator +(int value) const { return { x + value, y + value }; }
		inline Vec2 operator -(int value) const { return { x - value, y - value }; }
		inline Vec2 operator *(int value) const { return { x * value, y * value }; }
		inline Vec2 operator /(int value) const { return { x / value, y / value }; }
		
		inline Vec2 operator --() { return { x - 1, y - 1 }; }
		inline Vec2 operator ++() { return { x + 1, y + 1 }; }		
		inline bool operator ==(const Vec2& other) const { return (x == other.x && y == other.y) ? true : false; }
		inline bool operator !=(const Vec2& other) const { return (x != other.x && y != other.y) ? true : false; }
		inline bool operator >(Vec2 other) { return (magnitude() > other.magnitude()) ? true : false; }
		inline bool operator >=(Vec2 other) { return (magnitude() >= other.magnitude()) ? true : false; }
		inline bool operator <(Vec2 other) { return (magnitude() < other.magnitude()) ? true : false; }
		inline bool operator <=(Vec2 other) { return (magnitude() <= other.magnitude()) ? true : false; }
		friend std::ostream& operator<<(std::ostream& os, const Vec2& vector2d) {
			os << "X: " << vector2d.x << " Y: " << vector2d.y;
			return os;
		}
		operator Vec2f() { return { (f32)x,(f32)y }; }
	};

	//
	// Map pointer for Rendering, Collision and Trigger detection
	//
	struct Maps {
		i32* ColliderMap, * TriggerMap;
		DWORD* RenderMap;
	};

	struct sRGB {	//sRGB because RGB is already taken ;)
		i32 r, g, b;

		sRGB() = default;

		sRGB(i32 r, i32 g, i32 b) : r(r), g(g), b(b) {}

		inline void ToRGB(const Color& color) { r = GetBValue(color); g = GetGValue(color); b = GetRValue(color); }
		inline void operator()(i32 r, i32 g, i32 b) { this->r = r; this->g = g; this->b = b; }
		inline sRGB operator +(const sRGB& other) { return{ r + other.r, g + other.g,b + other.b }; }
		inline sRGB operator -(const sRGB& other) { return{ r - other.r, g - other.g,b - other.b }; }
		inline bool operator ==(const sRGB& other) { return (r == other.r && g == other.g && b == other.b) ? true : false; }
	};

	struct ParticlesSetting {
		Vec2 max, min, emission_point_min, emission_point_max;
		i32 emission, noise_factor;
		std::vector<Color> colors;
		Vec2f direction;
	};
}
//
// enum
//

// Input
namespace Keys {
	enum Keys : u32 {	//	<- No enum class because otherwise GetAsyncKeyState would't be able to read the key
		A = 0x41, B = 0x42, C = 0x43, D = 0x44, E = 0x45, F = 0x46, G = 0x47, H = 0x48, I = 0x49, J = 0x4A,
		K = 0x4B, L = 0x4C, M = 0x4D, N = 0x4E, O = 0x4F, P = 0x50, Q = 0x51, R = 0x52, S = 0x53, T = 0x54,
		U = 0x55, V = 0x56, W = 0x57, X = 0x58, Y = 0x59, Z = 0x5A, SPACE = 0x20
	};
}

// Colliders
enum class ColliderType {
	Static, Filled, Outline, None
};

// Describes the axis something can move on
enum class Axis {
	X, Y, Both
};


// Template stuff
template <typename CallBackType>
using cb_ptr = void(*)(CallBackType,CallBackType);

template <typename T>
inline constexpr bool is_Vec2 = std::_Is_any_of_v<std::remove_cv_t<T>, sur::Vec2>;

template <typename T>
concept VEC = is_Vec2<T>;	// Made with a concept because the variadic functionality is only availabe in templates 
