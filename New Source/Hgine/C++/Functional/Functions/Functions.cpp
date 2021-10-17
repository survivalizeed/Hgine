

#include "Functions.h"

#if _WIN32 || _WIN64
#if _WIN64
#else
void ErrorCatchAngelScript(const asSMessageInfo* msg, void* param)
{
    const char* type = "ERR ";
    if (msg->type == asMSGTYPE_WARNING)
        type = "WARN";
    else if (msg->type == asMSGTYPE_INFORMATION)
        type = "INFO";
    printf("%s (%d, %d) : %s : %s\n", msg->section, msg->row, msg->col, type, msg->message);
}
#endif
#endif

void sur::hgineInitialize(Vec2 window_size, Vec2 aspect_ratio, std::string_view resource_path, std::string_view sound_path)
{
    _window_size = window_size;
    _aspect_ratio = aspect_ratio;
    _resource_path = resource_path;
    _sound_path = sound_path;
    _render_buffer = new Color[window_size.x * window_size.y];

#if _WIN32 || _WIN64
#if _WIN64
#else
    _asEngine = asCreateScriptEngine();
    _asEngine->SetMessageCallback(asFUNCTION(ErrorCatchAngelScript), 0, asCALL_CDECL);
#endif
#endif
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
    if (pos.x < 0 || pos.x > _window_size.x - 1 || pos.y < 0 || pos.y > _window_size.y - 1)
        return;
    _render_buffer[pos.x + _window_size.x * pos.y] = color;
}

sur::Color sur::Get(Vec2 pos)
{
    if (pos.x < 0 || pos.x > _window_size.x - 1 || pos.y < 0 || pos.y > _window_size.y - 1)
        Color(0, 0, 0);
    return _render_buffer[pos.x + _window_size.y * pos.y];
}

bool sur::Vec2fBetween(Vec2f v, Vec2f min, Vec2f max)
{
    if (min.x <= v.x <= max.x && min.y <= v.y <= max.y)
        return true;
    return false;
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

//bool sur::PointLaysInside(const std::vector<Vec2f>& coords, Vec2f point)
//{
//    std::vector<Vec2> points;
//    for (i32 i = 0; i < coords.size() - 1; i += 2)
//        algorithm::DrawLine(coords[i], coords[i + 1], Color(0, 0, 0), [&](Vec2 p) {
//            points.push_back(p);
//        });
//    std::sort(points.begin(), points.end(), [](Vec2& v1, Vec2& v2) {
//        if (v1.y > v2.y)
//            return true;
//        else
//            return false;
//        }
//    );
//    i32 index = 0;
//    std::vector<Vec2> tmp;
//    for (i32 i = 0; i < points.size(); ++i) {
//        tmp.push_back(points[i]);
//        if (tmp[index].y != points[i].y)
//        {
//            tmp.erase(tmp.end() - 1);
//            if (tmp.size() >= 3) {
//                std::sort(tmp.begin(), tmp.end(), [](Vec2& v1, Vec2& v2) {
//                    if (v1.x < v2.x)
//                        return true;
//                    else
//                        return false;
//                    }
//                );
//            }
//            if (tmp[0].x > tmp[tmp.size() - 1].x)
//                std::swap(tmp[0].x, tmp[tmp.size() - 1].x);
//            if (!Vec2fBetween(point, { (f32)tmp[0].x, (f32)tmp[0].y }, { (f32)tmp[tmp.size() - 1].x, (f32)tmp[tmp.size() - 1].y })) {
//                return false;
//            }
//            tmp.clear();
//            index = 0;
//            i--;
//        }
//    }
//    return true;
//}

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
