

#include "Classes.h"
#include "../Functional/functional.h"

extern sur::Map_Analyses _Amap;

sur::Particles::Particles(sur::ParticlesSetting* settings) 
	: settings(settings)
{
	position = settings->emission_point_min;
	for (i32 i = 0; i < settings->emission; ++i) {
		// Calculating every position - the min position. So the minimal is always (0,0).
		Vec2 position(sur::RandomRange(settings->emission_point_min.x - settings->emission_point_min.x,
			settings->emission_point_max.x - settings->emission_point_min.x),
			sur::RandomRange(settings->emission_point_min.y - settings->emission_point_min.y,
				settings->emission_point_max.y - settings->emission_point_min.y));

		Color color = settings->colors.at(sur::RandomRange(0, (i32)settings->colors.size() - 1));
		Coords->push_back({ position,color });
		Offsets->push_back({ 0,0 }); // To allocate the memory we will need later
	}
}

void sur::Particles::Bind(bool Render)
{
	for (i32 i = 0; i < Offsets->size(); ++i) {
		i32 noise = sur::RandomRange(0, settings->noise_factor);
		i32 dir = sur::RandomRange(0, 4);
		if (dir == 0) Offsets->at(i).y -= noise; //W
		if (dir == 1) Offsets->at(i).x -= noise; //A
		if (dir == 2) Offsets->at(i).y += noise; //S
		if (dir == 3) Offsets->at(i).x += noise; //D
	}
	for (i32 i = 0; i < Coords->size(); ++i)
		_Amap.Render(Coords->at(i).pos + position + Offsets->at(i), Coords->at(i).color);
}
