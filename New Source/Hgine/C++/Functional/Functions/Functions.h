

#pragma once

#include "../../../Includes.h"

namespace sur 
{
	void wndInitialize(Vec2 window_size, Vec2 aspect_ratio, std::string_view resource_path, std::string_view sound_path);

	void PlayWAV(const std::string& path, u32 params, i32 volume);

	void SetVolume(i32 volume);

	i32 RandomRange(i32 min, i32 max);

	void Set(Vec2 pos, Color color);

	Color Get(Vec2 pos);

	Vec2f Absolute(Vec2f vec);

	f32 Distance(f32 first, f32 second);

	Vec2f Rotate2D(Vec2f position, Vec2f origin, i32 angle);

	Vec2f CalculateOrigin(const std::vector<Vec2f>& points);

	std::string GetExeDirectory();
}