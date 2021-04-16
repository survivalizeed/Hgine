

#include "Classes.h"
#include "../Functional/functional.h"

extern sur::Map_Analyses _Amap;

void sur::Particles::Bind(bool Render)
{
	if (!doonce) {
		for (i32 i = 0; i < settings->emission; ++i) {
			Vec2 position(sur::RandomRange(settings->emission_point_min.x, settings->emission_point_max.x),
				sur::RandomRange(settings->emission_point_min.y, settings->emission_point_max.y));	
			Color color = settings->colors.at(sur::RandomRange(0, settings->colors.size() - 1));
			Coords->push_back({ position,color});
		}
		doonce = true;
	}
	else {
		Vec2 move = MovQueue(settings->direction);
		for (i32 i = 0; i < Coords->size(); ++i) {
			i32 noise = sur::RandomRange(0, settings->noise_factor);
			i32 dir = sur::RandomRange(0, 4);
			if (dir == 0)	//W
				Coords->at(i).pos.y -= noise;
			if (dir == 1)	//A
				Coords->at(i).pos.x -= noise;
			if (dir == 2)	//S
				Coords->at(i).pos.y += noise;
			if (dir == 3)	//D
				Coords->at(i).pos.x += noise;
			Coords->at(i).pos = Coords->at(i).pos + move;
		}
	}
	for (i32 i = 0; i < Coords->size(); ++i)
		_Amap.Render(Coords->at(i).pos, Coords->at(i).color);
}