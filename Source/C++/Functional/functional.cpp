

#include "functional.h"

extern sur::Vec2 _window_size;
extern std::vector<i32> identitys;
extern std::vector<void*> ptrs;

sur::Maps sur::Initialize()
{
    eassert(_window_size.x == 0 || _window_size.y == 0, "_window_size not initialized");
    return { new i32[_window_size.x * _window_size.y], new i32[_window_size.x * _window_size.y],
            new Color[_window_size.x * _window_size.y] };
}

i32 sur::CharCounter(char Char, std::string_view Data)
{
    i32 counter = 0;
    for (i32 i = 0; i < Data.size(); i++)
    {
        if (Data[i] == Char)
        {
            counter++;
        }
    }
    return counter;
}

void sur::Sound(const std::string& path, u32 params, i32 volume)
{
    waveOutSetVolume(NULL, volume);
    PlaySoundA(path.c_str(), NULL, params);
}

void sur::SetVolume(i32 volume)
{
    waveOutSetVolume(NULL, volume);
}

i32 sur::RandomRange(i32 min, i32 max)
{
    static bool once = false;
    if (!once)
    {
        srand((u32)time(0));
        once = true;
    }
    return (min >= 0) ? rand() % (max - min + 1) + min : rand() % (max + min + 1) - min;
}

sur::Vec2f sur::Direction(Vec2f first, Vec2f second)
{
    bool xz = false, yz = false;
    Vec2f direction(first - second);
    if (direction.x == 0)
    {
        direction.x = 1;
        xz = true;
    }
    if (direction.y == 0)
    {
        direction.y = 1;
        yz = true;
    }
    direction.normalize();
    if (xz)
        direction.x = 0;
    if (yz)
        direction.y = 0;
    return direction;
}

void sur::MoveTowards(Master* const current, Master* const target, f32 speed, const Axis& axis,
    i32 MovQueueIndex, bool detect)
{
    assert(target->GetName() == "invalid" || current->GetName() == "invalid"); 
    Vec2f direction = sur::Direction(current->GetPosition(), target->GetPosition());
    switch (axis)
    {
    case Axis::X:
        direction.y = 0;
        break;
    case Axis::Y:
        direction.x = 0;
        break;
    default:
        break;
    }
    current->Move(direction * speed, MovQueueIndex, detect);
}

i64 sur::GetMilliseconds()
{
    using namespace std::chrono;
    return (i64)duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

sur::Vec3f sur::RotateX(Vec3f vec, Vec3f origin, i32 angle)
{
    Vec3f tmpv(origin - vec);
    Mat3x3 tmpm(
        1, 0, 0,
        0, cos(angle * PI / 180), -sin(angle * PI / 180),
        0, sin(angle * PI / 180), cos(angle * PI / 180));
    return tmpm.multiplyWithVector(tmpv) + origin;
}

sur::Vec3f sur::RotateY(Vec3f vec, Vec3f origin, i32 angle)
{
    Vec3f tmpv(origin - vec);
    Mat3x3 tmpm(
        cos(angle * PI / 180), 0, sin(angle * PI / 180),
        0, 1, 0,
        -sin(angle * PI / 180), 0, cos(angle * PI / 180));
    return tmpm.multiplyWithVector(tmpv) + origin;
}

sur::Vec3f sur::RotateZ(Vec3f vec, Vec3f origin, i32 angle)
{
    Vec3f tmpv(origin - vec);
    Mat3x3 tmpm(
        cos(angle * PI / 180), -sin(angle * PI / 180), 0,
        sin(angle * PI / 180), cos(angle * PI / 180), 0,
        0, 0, 1);
    return tmpm.multiplyWithVector(tmpv) + origin;
}

void sur::SetPixel(Vec2f position, Color color, i32 CollisionId, i32 TriggerId)
{
    _Amap.Render(ATS(position), color);
    if (CollisionId != 0)
        _Amap.Collider(ATS(position), CollisionId);
    if (CollisionId != 0)
        _Amap.Trigger(ATS(position), TriggerId);
}

sur::Vec2f sur::Absolute(Vec2f vec)
{
    if (vec.x < 0)
        vec.x *= -1;
    if (vec.y < 0)
        vec.y *= -1;
    return vec;
}

bool sur::InBetween(f32 first, f32 second, f32 max)
{
    if (abs(first - second) <= max)
        return true;
    else 
        return false;
}

bool sur::InBetweenPositive(f32 first, f32 second, f32 max)
{
    if (first - second <= max && first - second >= 0)
        return true;
    else
        return false;
}

bool sur::InBetweenNegative(f32 first, f32 second, f32 max)
{
    if (second - first >= -max && second - first <= 0)
        return true;
    else
        return false;
}
