

#pragma once

#include "../Functional/includes.h"

typedef signed char i8;
typedef	signed short i16;
typedef int i32;
typedef	long int i64;

typedef unsigned char u8;
typedef unsigned short u16;
typedef	unsigned int u32;
typedef unsigned long int u64;

typedef float f32;
typedef double f64;

typedef unsigned int Color;

typedef const int size;

constexpr int Second = 1000;
constexpr int Minute = 60000;
constexpr f32 PI = 3.1415926f;


// Colliders
enum class ColliderType {
	Static, Filled, Outline, None
};

// Describes the axis something can move on
enum class Axis {
	X, Y, Both
};

enum class Direction {
	Up, Down, Left, Right, None
};

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
		inline void normalize() { f32 mag = magnitude();  x /= mag; y /= mag; }

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
		
		inline Vec2 operator +=(const Vec2& other) { return { x += other.x, y += other.y }; }
		inline Vec2 operator -=(const Vec2& other) { return { x -= other.x, y -= other.y }; }
		
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
		operator Vec2f() {
			return { (f32)x, (f32)y };
		}
	};


	struct Mat2x2 {
		sur::Vec2f v1,v2;

		Mat2x2() = default;

		// { a | b }
		// { c | d }
		Mat2x2(f32 a, f32 b, f32 c, f32 d) {
			v1.x = a; v2.x = b; v1.y = c; v2.y = d;
		}

		Mat2x2(const Mat2x2& other) { 
			v1 = other.v1; v2 = other.v2;
		}


		inline Vec2 mulitplyWithVector(const Vec2f& other) {
			return { (i32)(v1.x * other.x + v2.x * other.y),(i32)(v1.y * other.x + v2.y * other.y)};
		}

		inline void multiplyWithMatrix(const Mat2x2& other) {
			sur::Vec2f tmp1 = mulitplyWithVector({ other.v1.x,other.v1.y });
			sur::Vec2f tmp2 = mulitplyWithVector({ other.v2.x, other.v2.y });
			v1 = tmp1; v2 = tmp2;
		}

		// { a | b }
		// { c | d }
		inline void operator()(f32 a, f32 b, f32 c, f32 d) {
			v1.x = a; v2.x = b; v1.y = c; v2.y = d;
		}

		inline f32 operator ()(i32 which, i32 index) {
			if (which == 0) if (index == 0) return v1.x;
			if (index == 1) return v1.y;
			if (which == 1) if (index == 0)	return v2.x;
			if (index == 1) return v2.y;
		}
		friend std::ostream& operator<<(std::ostream& os,const Mat2x2& mat) {
			os << "{ " << mat.v1.x << " " << mat.v2.x << " }" << "\n"
				<< "{ " << mat.v1.y << " " << mat.v2.y << " }";
			return os;
		}
	};
	//
	// Map pointer for Rendering, Collision and Trigger detection
	//
	struct Maps {
		i32* ColliderMap, * TriggerMap;
		Color* RenderMap;
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
		
		i32 emission, noise_factor;
		f32 max_distance_to_middle = 0;
		std::vector<Direction> block_directions;
		Vec2 emission_point_min, emission_point_max, middle;
		std::vector<Color> colors;
		ParticlesSetting() = default;

		//Update to take max and min if their time of usage has come
		ParticlesSetting(Vec2 emission_point_min, Vec2 emission_point_max, i32 emission, i32 noise_factor)
			: emission_point_max(emission_point_max), emission_point_min(emission_point_min),
			  emission(emission), noise_factor(noise_factor){}
	};
}
//
// enum
//

// Input
namespace Keys {
	enum Keys : u32 {	//	<- No enum class because otherwise GetAsyncKeyState would't be able to read the key
		None = 0,
		A = 0x41, B = 0x42, C = 0x43, D = 0x44, E = 0x45, F = 0x46, G = 0x47, H = 0x48, I = 0x49, J = 0x4A,
		K = 0x4B, L = 0x4C, M = 0x4D, N = 0x4E, O = 0x4F, P = 0x50, Q = 0x51, R = 0x52, S = 0x53, T = 0x54,
		U = 0x55, V = 0x56, W = 0x57, X = 0x58, Y = 0x59, Z = 0x5A, SPACE = 0x20
	};
}

// Template stuff
template <typename CallBackType>
using cb_ptr = void(*)(CallBackType,CallBackType);

template <typename T>
inline constexpr bool is_Vec2 = std::_Is_any_of_v<std::remove_cv_t<T>, sur::Vec2>;

template <typename T>
concept VEC = is_Vec2<T>;	// Made with a concept because the variadic functionality is only availabe in templates 
