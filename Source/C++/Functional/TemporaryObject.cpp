

#include "TemporaryObjects.h"

void sur::TMP::Line(Vec2f start, Vec2f end, Color color)
{
    Vec2 startINT = ATS(start);
    Vec2 endINT = ATS(end);
    if (startINT.y > endINT.y || startINT.x > endINT.x)
    {
        std::swap(startINT.y, endINT.y);
        std::swap(startINT.x, endINT.x);
    }
    if (startINT.x == endINT.x)
    {
        for (i32 i = startINT.y; i < endINT.y; ++i)
        {
            _Amap.Render(startINT.x, i, color);
        }
        return;
    }
    if (startINT.y == endINT.y)
    {
        for (i32 i = startINT.x; i < endINT.x; ++i)
        {
            _Amap.Render(i, startINT.y, color);
        }
        return;
    }
    i32 Dx, Dy;
    Dx = endINT.x - startINT.x;
    Dy = endINT.y - startINT.y;
    f32 RunsThrough = (f32)Dy / (f32)Dx;
    f32 counter = 0.0f;
    i32 countcounter = 1;
    if (RunsThrough >= 0)
    {
        i32 tempy = startINT.y;
        for (i32 i = startINT.x; i <= endINT.x; i++)
        {
            _Amap.Render(i, tempy, color);
            while (counter >= countcounter)
            {
                tempy++;
                _Amap.Render(i, tempy, color);
                countcounter++;
            }
            counter += RunsThrough;
        }
    }
    else
    {
        RunsThrough *= -1;
        i32 tempy = startINT.y;
        bool runned = false;
        for (i32 i = startINT.x; i <= endINT.x; i++)
        {
            _Amap.Render(i, tempy, color);
            while (counter >= countcounter)
            {
                tempy--;
                _Amap.Render(i, tempy, color);
                countcounter++;
            }
            runned = true;
            counter += RunsThrough;
        }
        if (!runned)
        {
            RunsThrough = (f32)Dx / (f32)Dy;
            RunsThrough *= -1;
            i32 tempx = startINT.x;
            for (i32 i = startINT.y; i <= endINT.y; i++)
            {
                _Amap.Render(tempx, i, color);
                while (counter >= countcounter)
                {
                    tempx--;
                    _Amap.Render(tempx, i, color);
                    countcounter++;
                }
                counter += RunsThrough;
            }
        }
    }
}

