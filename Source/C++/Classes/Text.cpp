

#include "Classes.h"

extern sur::Map_Analyses _Amap;

void sur::Text::Bind(bool Render) {
	Vec2 local = position;
	for (i32 i = 0; i < text.size(); ++i) {
		if (text[i] == 'A') {
			_Amap.Render(local, color);
			_Amap.Render(local.x + 1, local.y + 1, color);
			_Amap.Render(local.x + 2, local.y + 2, color);
			_Amap.Render(local.x + 3, local.y + 3, color);
			_Amap.Render(local.x + 4, local.y + 3, color);
			_Amap.Render(local.x + 5, local.y + 3, color);
			_Amap.Render(local.x + 6, local.y + 2, color);
			_Amap.Render(local.x + 7, local.y + 1, color);
			_Amap.Render(local.x + 8, local.y, color);
			local.x += 20;
		}
	}
}