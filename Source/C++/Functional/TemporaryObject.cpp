

#include "TemporaryObjects.h"

void sur::TMP::Line(Vec2 start, Vec2 end, Color color) {
	if (start.y > end.y || start.x > end.x) {
		std::swap(start.y, end.y);
		std::swap(start.x, end.x);
	}
	if (start.x == end.x) {
		for (i32 i = start.y; i < end.y; ++i) {
			_Amap.Render(start.x, i, color);
		}
		return;
	}
	if (start.y == end.y) {
		for (i32 i = start.x; i < end.x; ++i) {
			_Amap.Render(i, start.y, color);
		}
		return;
	}
	i32 Dx, Dy;
	f32 RunsThrough;
	Dx = end.x - start.x;
	Dy = end.y - start.y;
	RunsThrough = (f32)Dy / (f32)Dx;
	if (RunsThrough >= 0) {
		i32 tempy = start.y;
		f32 counter = 0.0f;
		i32 countcounter = 1;
		for (i32 i = start.x; i <= end.x; i++) {
			_Amap.Render(i, tempy, color);
			while (counter >= countcounter) {
				tempy++;
				_Amap.Render(i, tempy, color);
				countcounter++;
			}
			counter += RunsThrough;
		}
	}
	else {
		RunsThrough *= -1;
		i32 tempy = start.y;
		f32 counter = 0.0f;
		i32 countcounter = 1;
		bool runned = false;
		for (i32 i = start.x; i <= end.x; i++) {
			_Amap.Render(i, tempy, color);
			while (counter >= countcounter) {
				tempy--;
				_Amap.Render(i, tempy, color);
				countcounter++;
			}
			runned = true;
			counter += RunsThrough;
		}
		if (!runned) {
			RunsThrough = (f32)Dx / (f32)Dy;
			RunsThrough *= -1;
			i32 tempx = start.x;
			for (i32 i = start.y; i <= end.y; i++) {
				_Amap.Render(tempx, i, color);
				while (counter >= countcounter) {
					tempx--;
					_Amap.Render(tempx, i, color);
					countcounter++;
				}
				counter += RunsThrough;
			}
		}
	}
}