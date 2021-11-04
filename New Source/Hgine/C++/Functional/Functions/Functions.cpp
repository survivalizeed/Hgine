

#include "Functions.h"

void sur::hgineInitialize(Vec2 window_size, Vec2 aspect_ratio, std::string_view resource_path, std::string_view sound_path)
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

sur::i64 sur::GetMilliseconds()
{
    using namespace std::chrono;
    return (i64)duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
}

sur::i32 sur::RandomRange(i32 min, i32 max)
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
    pos += _camera_offset;
    if (pos.x < 0 || pos.x > _window_size.x - 1 || pos.y < 0 || pos.y > _window_size.y - 1)
        return;
    _render_buffer[pos.x + _window_size.x * pos.y] = Light::LightPixel(pos, color);
}

sur::Color sur::Get(Vec2 pos)
{
    if (pos.x < 0 || pos.x > _window_size.x - 1 || pos.y < 0 || pos.y > _window_size.y - 1)
        Color(0, 0, 0);
    return Light::LightPixel(pos, _render_buffer[pos.x + _window_size.y * pos.y]);
}

sur::Vec2f sur::Absolute(Vec2f vec)
{
    if (vec.x < 0)
        vec.x *= -1;
    if (vec.y < 0)
        vec.y *= -1;
    return vec;
}

sur::f32 sur::Distance(f32 first, f32 second)
{
    return abs(first - second);
}

sur::Vec2f sur::Rotate2D(Vec2f position, Vec2f origin, i32 angle)
{
    sur::Vec2 dist(ATS(position - origin));
    return STA(sur::Vec2((i32)(dist.x * cos(angle * PI / 180) + dist.y * sin(angle * PI / 180)),
        (i32)(dist.x * -sin(angle * PI / 180) + dist.y * cos(angle * PI / 180))) +
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

sur::Vec2f sur::GetSquareOrSpriteStart(const GameObject& obj)
{
    if (obj.GetType() == Type::Square)
        return static_cast<const Square&>(obj).start_point + static_cast<const Square&>(obj).position;
    if (obj.GetType() == Type::Sprite)
        return static_cast<const Sprite&>(obj).position;
    if (obj.GetType() == Type::ExtendedSprite)
        return static_cast<const ExtendedSprite&>(obj).position;
    return { 0.f, 0.f };
}

sur::Vec2f sur::GetSquareOrSpriteEnd(const GameObject& obj)
{
    if (obj.GetType() == Type::Square)
        return static_cast<const Square&>(obj).end_point + static_cast<const Square&>(obj).position;
    if (obj.GetType() == Type::Sprite)
        return static_cast<const Sprite&>(obj).position + static_cast<const Sprite&>(obj).size;
    if (obj.GetType() == Type::ExtendedSprite)
        return static_cast<const ExtendedSprite&>(obj).position + static_cast<const ExtendedSprite&>(obj).size;
    return { 0.f, 0.f };
}

std::string sur::GetExeDirectory()
{
    char buffer[MAX_PATH];
    GetModuleFileNameA(NULL, buffer, MAX_PATH);
    std::string f(buffer);
    return f.substr(0, f.find_last_of("\\/")) + "\\";
}



sur::Vec3f sur::CalculateOrigin3D(const std::vector<Vec3f>& points)
{
    Vec3f tmp;
    for (auto& iter : points) {
        tmp = tmp + iter;
    }
    return Vec3f(tmp.x / static_cast<f32>(points.size()), tmp.y / static_cast<f32>(points.size()), tmp.z / static_cast<f32>(points.size()));
}

std::vector<sur::Vec3f> sur::MeshTriangleContainerToVec3fs(const std::vector<TriangleContainer>& container)
{
    std::vector<Vec3f> points;
    for (i32 i = 0; i < container.size(); ++i) {
        points.push_back(container[i].a);
        points.push_back(container[i].b);
        points.push_back(container[i].c);
    }
    return points;
}

sur::Vec3f sur::Direction3D(Vec3f first, Vec3f second)
{
    bool xz = false, yz = false, zz = false;
    Vec3f direction(first - second);
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
    if (direction.z == 0)
    {
        direction.z = 1;
        zz = true;
    }
    direction.normalize();
    if (xz)
        direction.x = 0;
    if (yz)
        direction.y = 0;
    if (zz)
        direction.z = 0;
    return direction;
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
