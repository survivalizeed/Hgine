

#include "Classes.h"

extern sur::Map_Analyses _Amap;
extern std::vector<i32> identitys;
extern std::vector<void*> ptrs;

void sur::Triangle::LineVector::clear()
{
    memset(check, false, 3);
    Line1->clear();
    Line2->clear();
    Line3->clear();
}

std::vector<sur::Vec2>* sur::Triangle::LineVector::get(i32 i)
{
    switch (i)
    {
    case 1:
        check[0] = true;
        return this->Line1;
    case 2:
        check[1] = true;
        return this->Line2;
    case 3:
        check[2] = true;
        return this->Line3;
    default:
        return nullptr;
    }
}

std::vector<sur::Vec2>* sur::Triangle::LineVector::getother()
{
    if (!check[0])
    {
        check[0] = true;
        return this->Line1;
    }
    if (!check[1])
    {
        check[1] = true;
        return this->Line2;
    }
    if (!check[2])
    {
        check[2] = true;
        return this->Line3;
    }
    return nullptr;
}

void sur::Triangle::Line(Vec2 start, Vec2 end, std::vector<Vec2>* line, bool Render, bool Collider)
{
    auto Write = [=](i32 x, i32 y)
    {
        if (Render)
        {
            _Amap.Render({ x, y }, color);
        }
        if (Collider)
        {
            CollisionPos.push_back({ x, y });
            _Amap.Collider({ x, y }, id);
        }
    };
    if (start.y > end.y || start.x > end.x)
    {
        std::swap(start.y, end.y);
        std::swap(start.x, end.x);
    }
    if (start.x == end.x)
        start.x--;
    else
        line->push_back(start);
    position = { start.x, start.y };
    i32 Dx, Dy;
    f32 RunsThrough;
    Dx = end.x - start.x;
    Dy = end.y - start.y;
    RunsThrough = (f32)Dy / (f32)Dx;
    if (RunsThrough >= 0)
    {
        i32 tempy = start.y;
        f32 counter = 0.0f;
        i32 countcounter = 1;
        for (i32 i = start.x; i <= end.x; i++)
        {
            Write(i, tempy);
            while (counter >= countcounter)
            {
                tempy++;
                line->push_back({ i, tempy });
                Write(i, tempy);
                countcounter++;
            }
            counter += RunsThrough;
        }
    }
    else
    {
        RunsThrough *= -1;
        i32 tempy = start.y;
        f32 counter = 0.0f;
        i32 countcounter = 1;
        bool runned = false;
        for (i32 i = start.x; i <= end.x; i++)
        {
            Write(i, tempy);
            while (counter >= countcounter)
            {
                tempy--;
                line->push_back({ i, tempy });
                Write(i, tempy);
                countcounter++;
            }
            runned = true;
            counter += RunsThrough;
        }
        if (!runned)
        {
            RunsThrough = (f32)Dx / (f32)Dy;
            RunsThrough *= -1;
            i32 tempx = start.x;
            for (i32 i = start.y; i <= end.y; i++)
            {
                line->push_back({ tempx, i });
                Write(tempx, i);
                while (counter >= countcounter)
                {
                    tempx--;
                    Write(tempx, i);
                    countcounter++;
                }
                counter += RunsThrough;
            }
        }
    }
}

void sur::Triangle::Fill(LineVector& linevector)
{
    auto max_val = [](i32 a, i32 b, i32 c)
    {
        if (a >= b && a >= c)
            return 1;
        if (b >= a && b >= c)
            return 2;
        if (c >= a && c >= b)
            return 3;
        return 0;
    };
    auto min_val = [](i32 a, i32 b)
    { 
        return a <= b ? 1 : 2; 
    };
    auto near_comp = [](i32 target, i32 a, i32 b)
    { 
        return (abs(target - a) < abs(target - b)) ? 1 : 2; 
    };

    i32 maxv = max_val((i32)linevector.Line1->size(), (i32)linevector.Line2->size(), (i32)linevector.Line3->size());
    std::vector<sur::Vec2>* hypo = nullptr;
    std::vector<sur::Vec2>* other = nullptr;
    std::vector<sur::Vec2>* temp = nullptr;

    hypo = linevector.get(maxv);
    other = linevector.getother();
    temp = linevector.getother();

    assert(hypo->size() < 1 || other->size() < 1 || temp->size() < 1);

    if (hypo->at(0).y > hypo->at(hypo->size() - 1).y)
        std::reverse(hypo->begin(), hypo->end());
    if (other->at(0).y > other->at(other->size() - 1).y)
        std::reverse(other->begin(), other->end());
    if (temp->at(0).y > temp->at(temp->size() - 1).y)
        std::reverse(temp->begin(), temp->end());

    i32 dir = 0;
    if (near_comp(hypo->at(0).y, other->at(0).y, temp->at(0).y) == 1)
    {
        other->insert(other->end(), temp->begin(), temp->end()); //Ersetzen mit else unten
        dir = min_val(hypo->at(hypo->size() / 2).x, other->at(other->size() / 2).x);
        i32 counter = 0;
        for (i32 i = hypo->at(0).y; i < hypo->at(hypo->size() - 1).y; i++)
        {
            if (dir == 1)
            {
                if (counter < hypo->size() && counter < other->size())
                    for (i32 j = hypo->at(counter).x; j <= other->at(counter).x; j++)
                        _Amap.Render(j, i, color);
            }
            else
            {
                if (counter < hypo->size() && counter < other->size())
                    for (i32 j = other->at(counter).x; j <= hypo->at(counter).x; j++)
                        _Amap.Render(j, i, color);
            }
            counter++;
        }
    }
    else
    {
        temp->insert(temp->end(), other->begin(), other->end());
        dir = min_val(hypo->at(hypo->size() / 2).x, temp->at(temp->size() / 2).x);
        i32 counter = 0;
        for (i32 i = hypo->at(0).y; i < hypo->at(hypo->size() - 1).y; i++)
        {
            if (dir == 1)
            {
                if (counter < hypo->size() && counter < temp->size())
                    for (i32 j = hypo->at(counter).x; j <= temp->at(counter).x; j++)
                        _Amap.Render(j, i, color);
            }
            else
            {
                if (counter < hypo->size() && counter < temp->size())
                    for (i32 j = temp->at(counter).x; j <= hypo->at(counter).x; j++)
                        _Amap.Render(j, i, color);
            }
            counter++;
        }
    }
}

sur::Triangle::Triangle(Vec2f p1, Vec2f p2, Vec2f p3, Color color, std::string_view name, i32 id, const std::vector<int>& ignoreids,
    cb_ptr<Master*> callback)
    : p1(ATS(p1)), p2(ATS(p2)), p3(ATS(p3)), Master(name, id, color, callback)
{
    ignore = ignoreids;
    type = Type::Triangle;
    identitys.push_back(id);
    ptrs.push_back(this);
}

void sur::Triangle::Bind(bool Render, bool Collider)
{
    if (Collider)
        CollisionPos.clear();
    Line(p1, p2, linevector.Line1, Render, Collider);
    Line(p2, p3, linevector.Line2, Render, Collider);
    Line(p3, p1, linevector.Line3, Render, Collider);
    if (Render)
        Fill(linevector);
    linevector.clear();
}
