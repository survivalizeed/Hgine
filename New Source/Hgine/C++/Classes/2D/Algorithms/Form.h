

#pragma once

#include "../../../../Includes.h"

namespace sur::algorithm
{
	inline void DrawFormWire(const std::vector<Vec2f>& coords, Color color) 
	{
		for (i32 i = 0; i < static_cast<i32>(coords.size()) - 1; ++i) {
			DrawLine(ATS(coords[static_cast<size_t>(i)]), ATS(coords[static_cast<size_t>(i + 1)]), color, nullptr, nullptr);
		}
	}

	inline void DrawForm(const std::vector<Vec2f>& coords, Color color) 
	{
		std::vector<Vec2> wireForm;
		for (i32 i = 0; i < static_cast<i32>(coords.size()) - 1; ++i) {
			DrawLine(ATS(coords[static_cast<size_t>(i)]), ATS(coords[static_cast<size_t>(i + 1)]), color, nullptr,
				[&](Vec2 position) {
					wireForm.push_back(position);
				}
			);
		}
		DrawLine(ATS(coords[static_cast<size_t>(coords.size() - 1)]), ATS(coords[0]), color, nullptr,
			[&](Vec2 position) {
				wireForm.push_back(position);
			}
		);

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
