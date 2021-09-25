

#pragma once

#include "../../../../Includes.h"

namespace sur::algorithm
{
	inline void DrawFormWire(const std::vector<Vec2f>& coords, Color color)
	{
		for (i32 i = 0; i < static_cast<i32>(coords.size()) - 1; ++i) {
			DrawLine(coords[i], coords[static_cast<size_t>(i) + 1], color, nullptr, nullptr);
		}
	}

	//Not finished yet
	inline void DrawFormAuto(const std::vector<Vec2f>& coords, Color color)
	{
		std::vector<Vec2> wireForm;
		for (i32 i = 0; i < static_cast<i32>(coords.size()) - 1; ++i) {
			DrawLine(coords[i], coords[static_cast<size_t>(i) + 1], color, nullptr,
				[&](Vec2 position) {
					wireForm.push_back(position);
				}
			);
		}
		DrawLine(coords[coords.size() - 1], coords[0], color, nullptr,
			[&](Vec2 position) {
				wireForm.push_back(position);
			}
		);

		auto DrawHorLine = [&](i32 StartX, i32 EndX, i32 Y) {
			if (StartX > EndX)
				std::swap(StartX, EndX);
			for (i32 i = StartX; i < EndX; ++i) {
				Set({ i, Y }, color);
			}
		};

		std::sort(wireForm.begin(), wireForm.end(), [](Vec2& v1, Vec2& v2) {
			if (v1.y > v2.y)
				return true;
			else
				return false;
			}
		);
		bool except = false;
		i32 index = 0;
		std::vector<Vec2> tmp;
		for (i32 i = 0; i < wireForm.size(); ++i) {
			tmp.push_back(wireForm[i]);
			if (tmp[index].y != wireForm[i].y)
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
					DrawHorLine(tmp[0].x, tmp[tmp.size() - 1].x, tmp[0].y);
				}
				else {
					DrawHorLine(tmp[0].x, tmp[tmp.size() - 1].x, tmp[0].y);
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

	inline void DrawFormIndex(const std::vector<Vec2f>& coords, const std::vector<i32> indices, Color color) 
	{
		for (i32 i = 0; i < indices.size(); i += 3) {
			DrawTriangle(coords[indices[i]], coords[indices[i + 1]], coords[indices[i + 2]], color);
		}
	}
}



	