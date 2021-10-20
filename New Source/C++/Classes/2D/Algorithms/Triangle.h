

#pragma once

#include "../../../../Includes.h"

namespace sur::algorithm
{
	inline void DrawTriangleWire(Vec2f p1, Vec2f p2, Vec2f p3, Color color)
	{
		DrawLine(p1, p2, color, nullptr, nullptr);
		DrawLine(p2, p3, color, nullptr, nullptr);
		DrawLine(p3, p1, color, nullptr, nullptr);
	}

	inline void DrawTriangle(Vec2f p1, Vec2f p2, Vec2f p3, Color color) 
	{
		std::vector<Vec2> wireShape;
		DrawLine(p1, p2, color, nullptr, [&](Vec2 position)
			{
				wireShape.push_back(position);
			}
		);
		DrawLine(p2, p3, color, nullptr, [&](Vec2 position)
			{
				wireShape.push_back(position);
			}
		);
		DrawLine(p3, p1, color, nullptr, [&](Vec2 position)
			{
				wireShape.push_back(position);
			}
		);

		std::sort(wireShape.begin(), wireShape.end(), [](Vec2& v1, Vec2& v2) {
			if (v1.y > v2.y)
				return true;
			else
				return false;
			}
		);
		bool except = false;
		i32 index = 0;
		std::vector<Vec2> tmp;
		for (i32 i = 0; i < wireShape.size(); ++i) {
			tmp.push_back(wireShape[i]);
			if (tmp[index].y != wireShape[i].y)
			{
				tmp.erase(tmp.end() - 1);
				if (tmp.size() >= 3) {
					std::sort(tmp.begin(), tmp.end(), [](Vec2& v1, Vec2& v2) {
						if (v1.x < v2.x)
							return true;
						else
							return false;
						}
					);
				}
				if (tmp[0].x > tmp[tmp.size() - 1].x)
					std::swap(tmp[0].x, tmp[tmp.size() - 1].x);
				for (i32 c = tmp[0].x; c < tmp[tmp.size() - 1].x; ++c) {
					Set({ c, tmp[0].y }, color);
				}
				tmp.clear();
				index = 0;
				except = false;
				i--;
			}
			else {
				if (except)
					index++;
				except = true;
			}
		}
	}
}
