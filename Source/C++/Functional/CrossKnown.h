#pragma once

#include "includes.h"

extern sur::Vec2 _aspect;
extern sur::Vec2 _window_size;

struct CK {
	static sur::Vec2 ATS(const sur::Vec2f& vec) {
		if (vec.x == 0 && vec.y == 0) return { 0,0 };
		return 
		{ 
			i32((vec.x /*+ (0.5f * _aspect.x)*/) * (_window_size.x / _aspect.x)), 
			i32((vec.y /*+ (0.5f * _aspect.y)*/) * (_window_size.y / _aspect.y))
		};
	}

	static sur::Vec2f STA(const sur::Vec2& vec) {
		return {
			f32((vec.x /*- (0.5f * _window_size.x)*/) * ((f32)_aspect.x / (f32)_window_size.x)),
			f32((vec.y /*- (0.5f * _window_size.y)*/) * ((f32)_aspect.y / (f32)_window_size.y))
		};
	}

	static f32 Unit(i32 unit) {
		return f32(unit * ((f32)_aspect.x / (f32)_window_size.x));
	}

	static i32 Pixel(f32 unit) {
		return i32(unit * (_window_size.x / _aspect.x));
	}

};

#define ATS(vec) CK::ATS(vec)
#define STA(vec) CK::STA(vec)
#define Unit(px) CK::Unit(px)
#define Pixel(unit) CK::Pixel(unit)