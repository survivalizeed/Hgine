

#include "../Objects.h"

#include <codeanalysis\warnings.h>
#pragma warning( push )
#pragma warning ( disable : ALL_CODE_ANALYSIS_WARNINGS )
#include "../../../Lodepng/lodepng.h"
#pragma warning( pop )

sur::Font::Font(std::string_view file, Vec2 cellSize, i32 charCount, std::string_view align, Color colorToAlpha)
{
    this->align = align;
    std::vector<unsigned char> image;
    u32 width = 0, height = 0;
    static_cast<void>(lodepng::decode(image, width, height, file.data()));
    i32 x = 0;
    i32 y = 0;
    for (i32 i = 0; i < image.size(); i = i + 4) {
        all.colors.push_back(Color(image[i], image[static_cast<size_t>(i) + 1], image[static_cast<size_t>(i) + 2]));
        all.points.push_back({ x, y });
        x++;
        if (x >= static_cast<i32>(width)) {
            y++;
            x = 0;
        }
    }
    auto GetPixel = [&](Vec2 pos) -> Color {
        return all.colors[pos.x + width * pos.y];
    }; 
    for (i32 i = 0; i < charCount; ++i) {
        chars.push_back(Sprite("Empty", Sprite::FileType::Empty, {0,0}, Collider::None, "Empty", Color(0, 0, 0)));
        for (i32 x = 0; x < cellSize.x; ++x) {
            for (i32 y = 0; y < cellSize.y; ++y) {
                chars[i].points.push_back({ x,y });
            }
        }    
    }
    i32 incX = 0, incY = 0;
    for (i32 i = 0; i < charCount; ++i) {
        for (i32 x = 0; x < cellSize.x; ++x) {
            for (i32 y = 0; y < cellSize.y; ++y) {
                chars[i].colors.push_back(GetPixel({ x + incX * cellSize.x, y + incY * cellSize.y}));
            }
        }
        if ((incX + 2) * cellSize.x <= width) {
            incX++;
        }
        else {
            incY++;
            incX = 0;
        }
    }
    for (i32 i = 0; i < charCount; ++i) {
        for (auto& iter : chars[i].points) {
            iter.y = cellSize.y - iter.y;
        }
    }
    for(i32 c = 0; c < charCount; ++c){
        for (i32 i = 0; i < chars[c].colors.size(); ++i) {
            if (chars[c].colors[i] == colorToAlpha) {
                chars[c].colors.erase(chars[c].colors.begin() + i);
                chars[c].points.erase(chars[c].points.begin() + i);
                i--;
            }
        }
    }
    for (i32 i = 0; i < charCount; ++i) {
        std::vector<Vec2> tmp(chars[i].points);
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
        for (auto& iter : chars[i].points) {
            iter -= {minX, minY};
        }
        std::vector<Vec2> tmp2(chars[i].points);
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

        chars[i].size.x = Unit(maxX, Axis::X);
        chars[i].size.y = Unit(maxY, Axis::Y);
        chars[i].original_size = chars[i].size;
    }
}