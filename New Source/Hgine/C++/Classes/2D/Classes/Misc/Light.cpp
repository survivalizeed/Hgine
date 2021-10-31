

#include "../Objects.h"

sur::Light::Light(Vec2f position, f32 radius, f32 threshold, f32 falloffIntensity, Color color, std::string_view name)
{
	this->position = position;
    this->original_position = position;
	this->radius = radius;
	this->threshold = threshold;
	this->falloffIntensity = falloffIntensity;
	this->color = color;
    this->type = Type::Light;
    this->hash = static_cast<i32>(std::hash<std::string>{}(name.data()));
	_lights.push_back(this);
}

sur::Color sur::Light::LightPixel(Vec2 pos, Color color)
{
    if (!_use_light)
        return color;

    auto OverFlowCheck = [=](sRGB color) -> sRGB
    {
        if (color.r > 255)color.r = 255;
        if (color.r < 0) color.r = 0;
        if (color.g > 255) color.g = 255;
        if (color.g < 0) color.g = 0;
        if (color.b > 255) color.b = 255;
        if (color.b < 0) color.b = 0;
        return sRGB(color.r, color.g, color.b);
    };

    bool runned = false;
    sRGB expected(0, 0, 0);
    sRGB colorRGB(0, 0, 0);
    colorRGB.ToRGB(color);
    sRGB saved(0, 0, 0);
    for (auto& iter : _lights)
    {
        if (runned) {
            colorRGB = sRGB(0, 0, 0);
        }

        f32 maxDist = abs(iter->radius);

        expected.ToRGB(iter->color);

        Vec2f middle(iter->position);
        f32 dist = sur::Absolute(STA(pos) - middle).magnitude();
        if (dist == 0.f)
            dist = 1.f;

        if (dist > maxDist && maxDist != 0.f)
        {
            continue;
        }

        f32 tmpFalloffIntensity = (iter->falloffIntensity == 0) ? 1.f : iter->falloffIntensity;
        f32 tmpThreshold = (iter->threshold == 0) ? 1.f : iter->threshold;

        colorRGB = colorRGB + (sRGB(expected.r, expected.g, expected.b));
        colorRGB = sRGB(
            i32(colorRGB.r / ((dist * (tmpFalloffIntensity * dist)) / tmpThreshold)),
            i32(colorRGB.g / ((dist * (tmpFalloffIntensity * dist)) / tmpThreshold)),
            i32(colorRGB.b / ((dist * (tmpFalloffIntensity * dist)) / tmpThreshold))
        );
        if (!runned) {
            saved = colorRGB;
        }
        else {
            saved = saved + colorRGB;
        }
        runned = true;
    }
    if (!runned)
    {
        return OverFlowCheck(colorRGB * _ambient_light).ToColor();
    }
    sRGB tmp(0, 0, 0);
    tmp.ToRGB(color);
    return OverFlowCheck(saved + tmp * _ambient_light).ToColor();
}

sur::Vec2 sur::Light::Move(Vec2f direction, i32 moveQueueIndex)
{
    Vec2 move = MoveQueue(direction, moveQueueIndex);
    if (move.x == 0 && move.y == 0) return { 0, 0 };
    position += STA(move);
    return move;
}

