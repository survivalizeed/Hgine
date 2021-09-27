

#pragma once

#include "../../Includes.h"

typedef signed char i8;
typedef signed short i16;
typedef int i32;
typedef long int i64;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef float f32;
typedef double f64;

typedef u32 Color;

typedef const i32 size;

constexpr i32 Second = 1000;
constexpr i32 Minute = 60000;
constexpr f32 PI = 3.141f;

enum class Dimension
{
    X,
    Y,
    Z
};

namespace sur
{
    struct Vec2f
    {

        f32 x = 0, y = 0;

        Vec2f() = default;

        Vec2f(f32 x, f32 y) : x(x), y(y) {}

        Vec2f(const Vec2f& vector2d) : x(vector2d.x), y(vector2d.y) {}

        f32 magnitude()
        {
            return sqrt(x * x + y * y);
        }

        void invert()
        {
            x *= -1.f;
            y *= -1.f;
        }

        void normalize()
        {
            f32 mag = magnitude();
            x /= mag;
            y /= mag;
        }

        void absolute()
        {
            x = abs(x);
            x = abs(y);
        }

        void operator()(f32 x, f32 y)
        {
            this->x = x;
            this->y = y;
        }

        void operator()(const Vec2f& vector2d)
        {
            x = vector2d.x;
            y = vector2d.y;
        }

        void operator=(const Vec2f& vector2d)
        {
            x = vector2d.x;
            y = vector2d.y;
        }

        Vec2f operator+(const Vec2f& other) const { return { x + other.x, y + other.y }; }
        Vec2f operator-(const Vec2f& other) const { return { x - other.x, y - other.y }; }
        f32 operator*(const Vec2f& other) const { return x * other.x + y * other.y; }
        Vec2f operator/(const Vec2f& other) const { return { x / other.x, y / other.y }; }

        Vec2f operator+(f32 value) const { return { x + value, y + value }; }
        Vec2f operator-(f32 value) const { return { x - value, y - value }; }
        Vec2f operator*(f32 value) const { return { x * value, y * value }; }
        Vec2f operator/(f32 value) const { return { x / value, y / value }; }

        Vec2f operator+=(const Vec2f& other) { return { x += other.x, y += other.y }; }
        Vec2f operator-=(const Vec2f& other) { return { x -= other.x, y -= other.y }; }

        Vec2f operator--() { return { x - 1, y - 1 }; }
        Vec2f operator++() { return { x + 1, y + 1 }; }
        bool operator==(const Vec2f& other) const { return (x == other.x && y == other.y) ? true : false; }
        bool operator!=(const Vec2f& other) const { return (x != other.x && y != other.y) ? true : false; }

        friend std::ostream& operator<<(std::ostream& os, const Vec2f& vector2d)
        {
            os << "X: " << vector2d.x << " Y: " << vector2d.y;
            return os;
        }
    };

    struct Vec2
    {

        i32 x = 0, y = 0;

        Vec2() = default;

        Vec2(i32 x, i32 y) : x(x), y(y) {}

        Vec2(const Vec2& vector2d) : x(vector2d.x), y(vector2d.y) {}

        f32 magnitude()
        {
            return (f32)sqrt(pow(x, 2) + pow(y, 2));
        }

        void invert()
        {
            x *= -1;
            y *= -1;
        }

        void absolute()
        {
            x = abs(x);
            y = abs(y);
        }

        void operator()(i32 x, i32 y)
        {
            this->x = x;
            this->y = y;
        }

        void operator()(const Vec2& vector2d)
        {
            x = vector2d.x;
            y = vector2d.y;
        }

        void operator=(const Vec2& vector2d)
        {
            x = vector2d.x;
            y = vector2d.y;
        }

        Vec2 operator+(const Vec2& other) const { return { x + other.x, y + other.y }; }
        Vec2 operator-(const Vec2& other) const { return { x - other.x, y - other.y }; }
        i32 operator*(const Vec2& other) const { return x * other.x + y * other.y; }
        Vec2 operator/(const Vec2& other) const { return { x / other.x, y / other.y }; }

        Vec2 operator+(i32 value) const { return { x + value, y + value }; }
        Vec2 operator-(i32 value) const { return { x - value, y - value }; }
        Vec2 operator*(i32 value) const { return { x * value, y * value }; }
        Vec2 operator/(i32 value) const { return { x / value, y / value }; }

        Vec2 operator+=(const Vec2& other) { return { x += other.x, y += other.y }; }
        Vec2 operator-=(const Vec2& other) { return { x -= other.x, y -= other.y }; }

        Vec2 operator--() { return { x - 1, y - 1 }; }
        Vec2 operator++() { return { x + 1, y + 1 }; }
        bool operator==(const Vec2& other) const { return (x == other.x && y == other.y) ? true : false; }
        bool operator!=(const Vec2& other) const { return (x != other.x && y != other.y) ? true : false; }
       
        friend std::ostream& operator<<(std::ostream& os, const Vec2& vector2d)
        {
            os << "X: " << vector2d.x << " Y: " << vector2d.y;
            return os;
        }
    };

    struct Mat2x2
    {
        Vec2f v1, v2;

        Mat2x2() = default;

        // { a | b }
        // { c | d }
        Mat2x2(f32 a, f32 b, f32 c, f32 d)
        {
            v1.x = a;
            v2.x = b;
            v1.y = c;
            v2.y = d;
        }

        Mat2x2(const Mat2x2& other)
        {
            v1 = other.v1;
            v2 = other.v2;
        }

        Vec2 multiplyWithVector(const Vec2f& other)
        {
            return { (i32)(v1.x * other.x + v2.x * other.y), (i32)(v1.y * other.x + v2.y * other.y) };
        }

        void multiplyWithMatrix(const Mat2x2& other)
        {
            //sur::Vec2f tmp1 = multiplyWithVector({ other.v1.x, other.v1.y });
            //sur::Vec2f tmp2 = multiplyWithVector({ other.v2.x, other.v2.y });
            //v1 = tmp1;
            //v2 = tmp2;
        }

        // { a | b }
        // { c | d }
        void operator()(f32 a, f32 b, f32 c, f32 d)
        {
            v1.x = a;
            v2.x = b;
            v1.y = c;
            v2.y = d;
        }

        friend std::ostream& operator<<(std::ostream& os, const Mat2x2& mat)
        {
            os << "{ " << mat.v1.x << " " << mat.v2.x << " }"
                << "\n"
                << "{ " << mat.v1.y << " " << mat.v2.y << " }";
            return os;
        }
    };
    //
    // 3D stuff...
    //
    struct Vec3f
    {
        f32 x, y, z;

        Vec3f() = default;

        Vec3f(f32 x, f32 y, f32 z) : x(x), y(y), z(z) {}

        Vec3f(const Vec3f& other) : x(other.x), y(other.y), z(other.z) {}

        Vec2 toVec2() { return { (i32)x, (i32)y }; }

        f32 magnitude()
        {
            return sqrt(x * x + y * y + z * z);
        }

        void normalize()
        {
            f32 mag = magnitude();
            x /= mag;
            y /= mag;
            z /= mag;
        }

        Vec3f cross(const Vec3f& other) 
        {
            Vec3f tmp;
            tmp.x = y * other.z - z * other.y;
            tmp.y = z * other.x - x * other.z;
            tmp.z = x * other.y - y * other.x;
            return tmp;
        }

        f32 dot(const Vec3f& other) 
        {
            return x * other.x + y * other.y + z * other.z;
        }

        void operator()(f32 x, f32 y, f32 z)
        {
            this->x = x;
            this->y = y;
            this->z = z;
        }

        Vec3f operator+(const Vec3f& other) { return { x + other.x, y + other.y, z + other.z }; }
        Vec3f operator-(const Vec3f& other) { return { x - other.x, y - other.y, z - other.z }; }

        friend std::ostream& operator<<(std::ostream& os, const Vec3f& vector)
        {
            os << "X: " << vector.x << " Y: " << vector.y << " Z: " << vector.z;
            return os;
        }
    };

    struct Mat3x3
    {
        Vec3f v1, v2, v3;

        Mat3x3() = default;

        // { a | b | c }
        // { d | e | f }
        // { g | h | i }
        Mat3x3(f32 a, f32 b, f32 c, f32 d, f32 e, f32 f, f32 g, f32 h, f32 i) : v1(a, d, g), v2(b, e, h), v3(c, f, i) {}

        Mat3x3(const Mat3x3& other) : v1(other.v1), v2(other.v2), v3(other.v3) {}

        // { a | b | c }
        // { d | e | f }
        // { g | h | i }
        void operator()(f32 a, f32 b, f32 c, f32 d, f32 e, f32 f, f32 g, f32 h, f32 i)
        {
            v1(a, d, g);
            v2(b, e, h);
            v3(c, f, i);
        }

        Vec3f multiplyWithVector(const Vec3f& vec)
        {
            f32 xn, yn, zn;
            xn = v1.x * vec.x + v2.x * vec.y + v3.x * vec.z;
            yn = v1.y * vec.x + v2.y * vec.y + v3.y * vec.z;
            zn = v1.z * vec.x + v2.z * vec.y + v3.z * vec.z;
            return { xn, yn, zn };
        }

        friend std::ostream& operator<<(std::ostream& os, const Mat3x3& mat)
        {
            os << "{ " << mat.v1.x << " " << mat.v2.x << " " << mat.v3.x << " }"
                << "\n"
                << "{ " << mat.v1.y << " " << mat.v2.y << " " << mat.v3.y << " }"
                << "\n"
                << "{ " << mat.v1.z << " " << mat.v2.z << " " << mat.v3.z << " }";
            return os;
        }
    };

    struct sRGB
    { //sRGB because RGB is already taken ;)
        i32 r, g, b;

        sRGB() = default;

        sRGB(i32 r, i32 g, i32 b) : r(r), g(g), b(b) {}

        void ToRGB(const Color& color)
        {
            r = GetBValue(color);
            g = GetGValue(color);
            b = GetRValue(color);
        }

        Color ToColor() { return Color(r, g, b); }

        void operator()(i32 r, i32 g, i32 b)
        {
            this->r = r;
            this->g = g;
            this->b = b;
        }

        sRGB operator()(const sRGB& other)
        {
            r = other.r;
            g = other.g;
            b = other.b;
            return other;
        }

        sRGB operator+(const sRGB& other) { return { r + other.r, g + other.g, b + other.b }; }
        sRGB operator-(const sRGB& other) { return { r - other.r, g - other.g, b - other.b }; }
        sRGB operator/(const sRGB& other) { return { r / other.r, g / other.g, b / other.b }; }

        sRGB operator*(f32 value) { return { i32(r * value), i32(g * value), i32(b * value) }; }
        bool operator==(const sRGB& other) { return (r == other.r && g == other.g && b == other.b) ? true : false; }
    };

}

//
// enum
//

// Input
enum Keys : u32
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
    SPACE = 0x20
};

// Template stuff
template <typename CallBackType>
using cb_ptr = std::function<void(CallBackType, CallBackType)>;

