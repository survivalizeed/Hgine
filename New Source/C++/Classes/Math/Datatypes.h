

#pragma once

#include "../../../Includes.h"

namespace sur
{
    typedef signed char i8;
    typedef signed short i16;
    typedef int i32;
    typedef long int i64;

    typedef unsigned char u8;
    typedef unsigned short u16;
    typedef unsigned int u32;
    typedef unsigned long int u64;

    typedef float f32;
    typedef double f64;

    typedef u32 Color;

    constexpr i32 Second = 1000;
    constexpr i32 Minute = 60000;
    constexpr f32 PI = 3.14159f;

    template <typename CallBackType>
    using cb_ptr = std::function<void(CallBackType, CallBackType)>;

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

    enum class Dimension
    {

        X,
        Y,
        Z

    };

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

}