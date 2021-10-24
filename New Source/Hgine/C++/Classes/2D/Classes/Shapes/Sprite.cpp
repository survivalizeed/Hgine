

#include "../Objects.h"

#include <codeanalysis\warnings.h>
#pragma warning( push )
#pragma warning ( disable : ALL_CODE_ANALYSIS_WARNINGS )
#include "../../../Lodepng/lodepng.h"
#pragma warning( pop )


void sur::Sprite::LoadHgineres(std::string_view path)
{
    i32 x = 0, y = 0;

    std::string Data = "";
    std::string Nums = "0123456789";
    std::string ColorRef = "";
    std::ifstream file(path.data());
    if (file)
    {
        std::vector<i32> MaxX;
        std::ostringstream ss;
        ss << file.rdbuf();
        Data = ss.str();
        file.close();

        i32 count;
        for (i32 i = 0; i < Data.size(); i++)
        {
            if (Data[i] == '-')
                x++;
            if (Data[i] == 'E')
            {
                //Get X Value. It will be the last of the row. Here are (X,Y) the last of the row.
                y++;
                MaxX.push_back(x);
                x = 0;
            }
            if (Data[i] == '/')
            {
                for (i32 j = 1;; j++)
                {
                    count = 0;
                    for (i32 a = 0; a < Nums.size(); a++)
                        if (Data[i + j] == Nums[a])
                        {
                            ColorRef += Data[i + j];
                            count++;
                        }
                        else if (a == Nums.size() - 1 && count == 0)
                            goto Leave;
                }
            Leave:
                points.push_back({ x, y });
                colors.push_back(std::stoi(ColorRef));
                x++;
                ColorRef = "";
            }
        }
        for (i32 i = 0; i < colors.size(); ++i)
        {
            sRGB tmp(GetRValue(colors[i]), GetGValue(colors[i]), GetBValue(colors[i]));
            colors.at(i) = Color(tmp.r, tmp.g, tmp.b);
        }
        std::vector<Vec2> tmp(points);
        std::sort(tmp.begin(), tmp.end(), [](Vec2& l, Vec2& r) {
            if (l.y > r.y)
                return true;
            else
                return false;
            }
        );
        i32 maxY = tmp[0].y;

        for (auto& iter : points)
        {
            iter.y = maxY - iter.y;
        }
        size.x = Unit(*std::max_element(MaxX.begin(), MaxX.end()) - 1, Axis::X);
        size.y = Unit(y - 1, Axis::Y);
        original_size = size;
    }
}

void sur::Sprite::LoadPng(std::string_view path, Color colorToAlpha)
{
    std::vector<unsigned char> image; 
    u32 width = 0, height = 0;
    static_cast<void>(lodepng::decode(image, width, height, path.data()));

    size.x = Unit(width - 1, Axis::X);
    size.y = Unit(height - 1, Axis::Y);

    i32 x = 0;
    i32 y = 0;
    for (i32 i = 0; i < image.size(); i = i + 4) {
        this->colors.push_back(Color(image[i], image[static_cast<size_t>(i) + 1], image[static_cast<size_t>(i) + 2]));
        this->points.push_back({ x, y });
        x++;
        if (x >= static_cast<i32>(width)) {
            y++;
            x = 0;
        }
    }
    for (auto& iter : points) {
        iter.y = height - iter.y;
    }
    for (i32 i = 0; i < colors.size(); ++i) {
        if (colors[i] == colorToAlpha) {
            colors.erase(colors.begin() + i);
            points.erase(points.begin() + i);
            i--;
        }
    }
    std::vector<Vec2> tmp(points);
    std::sort(tmp.begin(), tmp.end(), [](Vec2& l, Vec2& r) {
        if (l.x < r.x)
            return true;
        else
            return false;
        }
    );
    i32 minX = tmp[0].x;
    std::sort(tmp.begin(), tmp.end(), [](Vec2& l, Vec2& r) {
        if (l.y < r.y)
            return true;
        else
            return false;
        }
    );
    i32 minY = tmp[0].y;
    for (auto& iter : points) {
        iter -= {minX, minY};
    }
    std::vector<Vec2> tmp2(points);
    std::sort(tmp2.begin(), tmp2.end(), [](Vec2& l, Vec2& r) {
        if (l.x > r.x)
            return true;
        else
            return false;
        }
    );
    i32 maxX = tmp2[0].x;
    std::sort(tmp2.begin(), tmp2.end(), [](Vec2& l, Vec2& r) {
        if (l.y > r.y)
            return true;
        else
            return false;
        }
    );
    i32 maxY = tmp2[0].y;

    size.x = Unit(maxX, Axis::X);
    size.y = Unit(maxY, Axis::Y);
    original_size = size;
}

sur::Sprite::Sprite(std::string_view file, FileType filetype, Vec2f position, Collider collider, std::string_view name, Color colorToAlpha)
{
    this->color = Color(0, 0, 0);
    this->position = position;
    this->type = Type::Sprite;
    this->collider = collider;
    this->name = name;
    this->hash = static_cast<i32>(std::hash<std::string>{}(name.data()));
    _gameObjects.push_back(this);

    if (filetype == FileType::Hgineres)
        LoadHgineres(file);
    else if (filetype == FileType::PNG)
        LoadPng(file, colorToAlpha);
}

void sur::Sprite::Scale(Vec2f scaleOrigin, Vec2f scale)
{
    this->scaleOrigin = scaleOrigin;
    size.x = original_size.x * scale.x;
    size.y = original_size.y * scale.y;
    this->scale(
        scale.x, 0, 0,
        0, scale.y, 0,
        0, 0, 1
    );
}

void sur::Sprite::Bind(bool render)
{
    if (collider != Collider::None)
        CheckCollision();
    for (i32 i = 0; i < points.size(); ++i)
        Set(ATS(scale.Forward2D(STA(points[i]) - scaleOrigin) + scaleOrigin) + ATS(position), colors[i]);
}
