

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
            {
                x++;
            }
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
                    {
                        if (Data[i + j] == Nums[a])
                        {
                            ColorRef += Data[i + j];
                            count++;
                        }
                        else if (a == Nums.size() - 1 && count == 0)
                        {
                            goto Leave;
                        }
                    }
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
        this->size.x = *std::max_element(MaxX.begin(), MaxX.end());
        this->size.y = y;
    }
}

void sur::Sprite::LoadPng(std::string_view path)
{
    std::vector<unsigned char> image; 
    u32 width = 0, height = 0;
    static_cast<void>(lodepng::decode(image, width, height, path.data()));

    i32 x = 0;
    i32 y = 0;
    for (i32 i = 0; i < image.size(); i = i + 4) {
        this->colors.push_back(Color(image[i], image[static_cast<size_t>(i) + 1], image[static_cast<size_t>(i) + 2]));
        this->points.push_back({ x, y });
        ++x;
        if (x >= width) {
            ++y;
            x = 0;
        }
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

}

sur::Sprite::Sprite(std::string_view path, FileType filetype, Vec2f position, std::string_view name)
{

    this->color = Color(0, 0, 0);
    this->position = position;
    this->type = Type::Sprite;
    this->name = name;
    this->hash = static_cast<i32>(std::hash<std::string>{}(name.data()));

    if (filetype == FileType::Hgineres)
        LoadHgineres(path);
    if (filetype == FileType::PNG)
        LoadPng(path);
}

void sur::Sprite::Bind(bool render)
{
    for (i32 i = 0; i < points.size(); ++i)
        Set(points[i] + ATS(position), colors[i]);
}