

#pragma once

#include "../../../../Includes.h"

namespace sur
{
	void Set(Vec2, Color);	// Definition in Functions.cpp
}

namespace sur::algorithm
{
	// Set both last parameters to "nullptr" if you don't want to invoke code.
	// If you set both last parameters to "nullptr" the line will just display.
	// The OnPixelYBreak function will be mostly used by the triangle algorithm.
	inline void DrawLine(Vec2f start_point, Vec2f end_point, Color color, std::function<void(Vec2)> OnPixelSet = nullptr, 
		std::function<void(Vec2)> OnPixelYBreak = nullptr) 
	{
		if (OnPixelSet == nullptr)
			OnPixelSet = [&](Vec2 position) {
				Set(position, color);
			};
		if (OnPixelYBreak == nullptr)
			OnPixelYBreak = [](Vec2){};

		Vec2 start = ATS(start_point);
		Vec2 end = ATS(end_point);
		
		if (start.x > end.x || start.y > end.y)
			std::swap(start, end);

		// The Stuff in there will be exectued if the start.x and end.x or start.y and end.y are the same. 
		// The reason why I did this is because we will get a higher performance for just a bit more of code :)
		{
			if (start.x == end.x) {
				for (i32 i = start.y; i <= end.y; ++i) {
					OnPixelSet({ start.x, i });
					OnPixelYBreak({ start.x, i });
				}
				return;
			}
			if (start.y == end.y) {
				OnPixelYBreak(start);
				for (i32 i = start.x; i <= end.x; ++i) {
					OnPixelSet({ i, start.y });				
				}
				return;
			}
		}

		Vec2 distance = end - start;
		f32 lnBreakRatio = static_cast<f32>(distance.y) / static_cast<f32>(distance.x),
			iterCount = 0.f;
		i32 lnBreakCount = 1;

		if (lnBreakRatio >= 0) {
			OnPixelYBreak(start);
			for (i32 i = start.x; i <= end.x; ++i) {
				OnPixelSet({ i, start.y });
				while (iterCount >= lnBreakCount) {
					start.y++;
					OnPixelSet({ i, start.y });
					OnPixelYBreak({ i, start.y });
					lnBreakCount++;
				}
				iterCount += lnBreakRatio;
			}
		}
		else {
			lnBreakRatio *= -1.f;
			bool runned = false;
			for (i32 i = start.x; i <= end.x; ++i) {
				if(!runned)
					OnPixelYBreak(start);
				OnPixelSet({ i, start.y });
				while (iterCount >= lnBreakCount) {
					start.y--;
					OnPixelSet({ i, start.y });
					OnPixelYBreak({ i, start.y });
					lnBreakCount++;
				}
				runned = true;
				iterCount += lnBreakRatio;
			}
			if (!runned) {
				lnBreakRatio = (static_cast<f32>(distance.x) / static_cast<f32>(distance.y)) * -1.f;
				for (i32 i = start.y; i <= end.y; i++) {
					OnPixelYBreak({ start.x, i });
					OnPixelSet({ start.x, i });
					while (iterCount >= lnBreakCount) {
						start.x--;
						OnPixelSet({ start.x, i });
						lnBreakCount++;
					}
					iterCount += lnBreakRatio;
				}
			}
		}
		OnPixelYBreak(end);
	}
}