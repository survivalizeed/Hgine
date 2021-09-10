

#include "../Objects.h"

sur::Sprite::Sprite(std::string_view path, Vec2f position, std::string_view name)
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
        size.x = *std::max_element(MaxX.begin(), MaxX.end());
        size.y = y;
        this->color = Color(0, 0, 0);
        this->position = position;
        this->type = Type::Sprite;
        this->name = name;
        this->hash = static_cast<i32>(std::hash<std::string>{}(name.data()));
    }
}

void sur::Sprite::Bind(bool render)
{
    for (i32 i = 0; i < points.size(); ++i)
        Set(points[i] + ATS(position), colors[i]);
}
