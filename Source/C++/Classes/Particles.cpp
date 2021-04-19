

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
		if((settings->middle - (Coords->at(i).pos + position + Offsets->at(i))).magnitude() > settings->max_distance_to_middle 
			&& settings->max_distance_to_middle != 0.f){
			Vec2f dir(sur::Direction(settings->middle, Coords->at(i).pos + position + Offsets->at(i)));
			Offsets->at(i) = Offsets->at(i) + Vec2((i32)ceil(dir.x * noise * 3), (i32)ceil(dir.y * noise * 3));
			continue;
		}
		if (std::find(settings->block_directions.begin(), settings->block_directions.end(), Direction::Up)
			== settings->block_directions.end() && dir == 0) Offsets->at(i).y -= noise; //W
		if (std::find(settings->block_directions.begin(), settings->block_directions.end(), Direction::Left)
			== settings->block_directions.end() && dir == 1) Offsets->at(i).x -= noise; //A
		if (std::find(settings->block_directions.begin(), settings->block_directions.end(), Direction::Down)
			== settings->block_directions.end() && dir == 2) Offsets->at(i).y += noise; //S
		if (std::find(settings->block_directions.begin(), settings->block_directions.end(), Direction::Right)
			== settings->block_directions.end() && dir == 3) Offsets->at(i).x += noise; //D
	}
	for (i32 i = 0; i < Coords->size(); ++i)
		_Amap.Render(Coords->at(i).pos + position + Offsets->at(i), Coords->at(i).color);
}


void sur::Particles::MoveTowards(sur::Vec2 position, f32 speed)
{
	auto calculate = [&](i32 start, i32 end) {
		for (i32 i = start; i < end; ++i) { 
			Vec2f dir(sur::Direction(position, Coords->at(i).pos + this->GetPosition() + Offsets->at(i)));
			Vec2 move = Coords->at(i).MovQueue(dir * speed);
			if (move.x == 0 && move.y == 0) continue;
			Offsets->at(i) = Offsets->at(i) + move;
		}
	};
	for (i32 i = 0; i < Offsets->size(); ++i) {
		Vec2f dir(sur::Direction(position,Coords->at(i).pos + this->position + Offsets->at(i)));
		Vec2 move = Coords->at(i).MovQueue(dir * speed);
		if (move.x == 0 && move.y == 0) continue;
		Offsets->at(i) = Offsets->at(i) + move;
	}
}
