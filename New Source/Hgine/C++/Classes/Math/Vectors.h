

#pragma once

#include "../../../Includes.h"

namespace sur
{
    template<typename T>
    struct Vec2_Original
    {

        T x = 0, y = 0;

        Vec2_Original() = default;

        Vec2_Original(T x, T y) : x(x), y(y) {}

        Vec2_Original(const Vec2_Original& vector2d) : x(vector2d.x), y(vector2d.y) {}

        f32 magnitude()
        {
            return sqrtf(static_cast<f32>(x * x) + static_cast<f32>(y * y));
        }

        void invert()
        {
            x *= -1.f;
            y *= -1.f;
        }

        bool isZero()
        {
            return x == 0 && y == 0 ? true : false;
        }

        void closerToZeroByOne()
        {
            if (x > 0) 
                x--;
            else if (x < 0)
                x++;
            if (y > 0)
                y--;
            else if (y < 0) 
                y++;
        }

        void absolute()
        {
            x = abs(x);
            x = abs(y);
        }

        void normalize()
        {
            f32 mag = magnitude();
            x /= mag;
            y /= mag;
        }

        void operator()(T x, T y)
        {
            this->x = x;
            this->y = y;
        }

        void operator()(const Vec2_Original& vector2d)
        {
            x = vector2d.x;
            y = vector2d.y;
        }

        void operator=(const Vec2_Original& vector2d)
        {
            x = vector2d.x;
            y = vector2d.y;
        }

        Vec2_Original operator+(const Vec2_Original& other) const { return { x + other.x, y + other.y }; }
        Vec2_Original operator-(const Vec2_Original& other) const { return { x - other.x, y - other.y }; }
        Vec2_Original operator/(const Vec2_Original& other) const { return { x / other.x, y / other.y }; }

        Vec2_Original operator+(f32 value) const { return { x + value, y + value }; }
        Vec2_Original operator-(f32 value) const { return { x - value, y - value }; }
        Vec2_Original operator*(f32 value) const { return { x * value, y * value }; }
        Vec2_Original operator/(f32 value) const { return { x / value, y / value }; }

        Vec2_Original operator+=(const Vec2_Original& other) { return { x += other.x, y += other.y }; }
        Vec2_Original operator-=(const Vec2_Original& other) { return { x -= other.x, y -= other.y }; }

        void operator--() { x -= 1; y -= 1; }
        void operator++() { x += 1; y += 1; }
        
        Vec2_Original operator-() {
            Vec2_Original tmp(*this);
            tmp.invert();
            return tmp;
        }

        bool operator==(const Vec2_Original& other) const { return (x == other.x && y == other.y) ? true : false; }
        bool operator!=(const Vec2_Original& other) const { return (x != other.x && y != other.y) ? true : false; }

        friend std::ostream& operator<<(std::ostream& os, const Vec2_Original& vector2d)
        {
            os << "X: " << vector2d.x << " Y: " << vector2d.y;
            return os;
        }
    };

    using Vec2f = Vec2_Original<f32>;
    using Vec2 = Vec2_Original<i32>;

    struct Vec3f
    {

        f32 x = 0.f, y = 0.f, z = 0.f;

        Vec3f() = default;

        Vec3f(f32 x, f32 y, f32 z) : x(x), y(y), z(z) {}

        Vec3f(const Vec3f& other) : x(other.x), y(other.y), z(other.z) {}

        f32 magnitude()
        {
            return sqrt(x * x + y * y + z * z);
        }

        void invert()
        {
            x *= -1.f;
            y *= -1.f;
            z *= -1.f;
        }

        void absolute() 
        {
            x = abs(x);
            y = abs(y);
            z = abs(z);
        }

        void normalize()
        {
            f32 mag = magnitude();
            x /= mag;
            y /= mag;
            z /= mag;
        }

        Vec2 toVec2()
        {
            return { (i32)x, (i32)y };
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

        Vec3f operator+(const Vec3f& other) const { return { x + other.x, y + other.y, z + other.z }; }
        Vec3f operator-(const Vec3f& other) const { return { x - other.x, y - other.y, z - other.z }; }
        Vec3f operator/(const Vec3f& other) const { return { x / other.x, y / other.y, z / other.z }; }

        Vec3f operator+(f32 value) const { return { x + value, y + value, z + value }; }
        Vec3f operator-(f32 value) const { return { x - value, y - value, z - value }; }
        Vec3f operator*(f32 value) const { return { x * value, y * value, z * value }; }
        Vec3f operator/(f32 value) const { return { x / value, y / value, z / value }; }

        Vec3f operator+=(const Vec3f& other) { return { x += other.x, y += other.y, z += other.z }; }
        Vec3f operator-=(const Vec3f& other) { return { x -= other.x, y -= other.y, z -= other.z }; }

        void operator--() { x -= 1; y -= 1; z -= 1; }
        void operator++() { x -= 1; y -= 1; z -= 1; }

        bool operator==(const Vec3f& other) const { return (x == other.x && y == other.y && z == other.z) ? true : false; }
        bool operator!=(const Vec3f& other) const { return (x != other.x && y != other.y && z != other.z) ? true : false; }

        friend std::ostream& operator<<(std::ostream& os, const Vec3f& vector)
        {
            os << "X: " << vector.x << " Y: " << vector.y << " Z: " << vector.z;
            return os;
        }

    };
}
