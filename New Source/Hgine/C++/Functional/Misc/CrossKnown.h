

#pragma once

#include "../../../Includes.h"

namespace sur 
{
	enum class Axis
	{

		X,
		Y

	};

	// ATS = Aspect To Screen
	inline Vec2 ATS(const Vec2f& vec) 
	{
		if (vec.x == 0.f && vec.y == 0.f) return { 0,0 };
		return
		{
			static_cast<i32>(static_cast<f32>(vec.x * static_cast<f32>(_window_size.x) / static_cast<f32>(_aspect_ratio.x))),
			static_cast<i32>(static_cast<f32>(vec.y * static_cast<f32>(_window_size.y) / static_cast<f32>(_aspect_ratio.y)))
		};
	}

	// STA = Screen To Aspect
	inline Vec2f STA(const Vec2& vec) 
	{
		if (vec.x == 0 && vec.y == 0) return { 0.f,0.f };
		return {
			static_cast<f32>(vec.x) * static_cast<f32>(_aspect_ratio.x) / static_cast<f32>(_window_size.x),
			static_cast<f32>(vec.y) * static_cast<f32>(_aspect_ratio.y) / static_cast<f32>(_window_size.y)
		};
	}

	inline f32 Unit(i32 unit, Axis axis) 
	{
		if (axis == Axis::Y)
			static_cast<f32>(unit) * (static_cast<f32>(_aspect_ratio.y) / static_cast<f32>(_window_size.y));
		return static_cast<f32>(unit) * (static_cast<f32>(_aspect_ratio.x) / static_cast<f32>(_window_size.x));
	}

	inline i32 Pixel(f32 unit, Axis axis) 
	{
		if (axis == Axis::Y)
			static_cast<i32>(static_cast<f32>(unit * static_cast<f32>(_window_size.y) / static_cast<f32>(_aspect_ratio.y)));
		return static_cast<i32>(static_cast<f32>(unit * static_cast<f32>(_window_size.x) / static_cast<f32>(_aspect_ratio.x)));
	}
}