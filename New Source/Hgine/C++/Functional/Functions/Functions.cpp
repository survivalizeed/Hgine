

#include "Functions.h"

void sur::wndInitialize(Vec2 window_size, Vec2 aspect_ratio, std::string_view resource_path, std::string_view sound_path)
{
    _window_size = window_size;
    _aspect_ratio = aspect_ratio;
    _resource_path = resource_path;
    _sound_path = sound_path;
    _render_buffer = new Color[window_size.x * window_size.y];
#ifdef _DEBUG
    if (_window_size.x == 0 || _window_size.y == 0) {
        Error("_window_size can't have x or y be 0");
    }
    if (_aspect_ratio.x < 1 || _aspect_ratio.y < 1) {
        Error("_aspect_ratio.x or _aspect_ratio.y can't be smaller than 1");
    }
    if (_window_size.x / _aspect_ratio.x > 25 || _window_size.y / _aspect_ratio.y > 25) {
        Reminder("Having an aspect ratio too small depending on the window size can lead to uncorrectness of the positioning");
    }
#endif
}

void sur::PlayWAV(const std::string& path, u32 params, i32 volume)
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

void sur::Set(Vec2 pos, Color color)
{
    if (pos.x < 0 || pos.x > _window_size.x - 1 || pos.y < 0 || pos.y > _window_size.y - 1)
        return;
    _render_buffer[pos.x + _window_size.y * pos.y] = color;
}

Color sur::Get(Vec2 pos)
{
    if (pos.x < 0 || pos.x > _window_size.x - 1 || pos.y < 0 || pos.y > _window_size.y - 1)
        Color(0, 0, 0);
    return _render_buffer[pos.x + _window_size.y * pos.y];
}

sur::Vec2f sur::Absolute(Vec2f vec)
{
    if (vec.x < 0)
        vec.x *= -1;
    if (vec.y < 0)
        vec.y *= -1;
    return vec;
}

f32 sur::Distance(f32 first, f32 second)
{
    return abs(first - second);
}

sur::Vec2f sur::Rotate2D(Vec2f position, Vec2f origin, i32 angle)
{
    sur::Vec2 dist(ATS(position - origin));
    return STA(sur::Vec2((i32)(dist.x * cos(angle * PI / 180) - dist.y * sin(angle * PI / 180)),
        (i32)(dist.x * sin(angle * PI / 180) + dist.y * cos(angle * PI / 180))) +
        ATS(origin));
}

sur::Vec2f sur::CalculateOrigin(const std::vector<Vec2f>& points)
{
    Vec2f tmp;
    for (auto& iter : points) {
        tmp += iter;
    }
    return tmp / static_cast<f32>(points.size());
}
