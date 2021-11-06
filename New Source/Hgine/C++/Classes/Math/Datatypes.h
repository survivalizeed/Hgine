

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

    template <typename CallBackType>
    using cb_ptr_s = std::function<void(CallBackType)>;

    struct H_RGB
    {

        i32 r = 0, g = 0, b = 0;

        H_RGB() = default;

        H_RGB(i32 r, i32 g, i32 b) : r(r), g(g), b(b) {}

        void ToRGB(const Color& color)
        {
            r = GetBValue(color);
            g = GetGValue(color);
            b = GetRValue(color);
        }

        Color ToColor() 
        { 
            return Color(r, g, b); 
        }

        void operator()(i32 r, i32 g, i32 b)
        {
            this->r = r;
            this->g = g;
            this->b = b;
        }

        H_RGB operator()(const H_RGB& other)
        {
            r = other.r;
            g = other.g;
            b = other.b;
            return other;
        }

        H_RGB operator+(const H_RGB& other) { return { r + other.r, g + other.g, b + other.b }; }
        H_RGB operator-(const H_RGB& other) { return { r - other.r, g - other.g, b - other.b }; }
        H_RGB operator/(const H_RGB& other) { return { r / other.r, g / other.g, b / other.b }; }

        H_RGB operator*(f32 value) { return { i32(r * value), i32(g * value), i32(b * value) }; }
        bool operator==(const H_RGB& other) { return (r == other.r && g == other.g && b == other.b) ? true : false; }

    };

    enum class Dimension
    {

        X,
        Y,
        Z

    };

}