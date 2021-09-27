

#include "../Objects.h"

sur::ParticleSystem::ParticleSystem(ParticleSettings* settings)
{
	this->settings = settings;
	settings->middle(
		f32(settings->emission_point_minimal.x + 0.5f * (settings->emission_point_maximal.x - settings->emission_point_minimal.x)),
		f32(settings->emission_point_minimal.y + 0.5f * (settings->emission_point_maximal.y - settings->emission_point_minimal.y))
	);
	for (i32 i = 0; i < settings->emission; ++i) {
		Vec2 local_position(
			sur::RandomRange(0, Pixel(settings->emission_point_maximal.x - settings->emission_point_minimal.x)),
			sur::RandomRange(0, Pixel(settings->emission_point_maximal.y - settings->emission_point_minimal.y))
		);
		Color color = settings->colors[static_cast<size_t>(sur::RandomRange(0, static_cast<i32>(settings->colors.size()) - 1))];
		particles.push_back({ local_position, color });
		offsets.push_back({ 0,0 });
	}
}

void sur::ParticleSystem::Bind(bool render)
{
	for (i32 i = 0; i < offsets.size(); ++i) {
		i32 noise = sur::RandomRange(settings->min_noise, settings->max_noise);
		i32 dir = sur::RandomRange(0, 8);
		if ((ATS(settings->middle) - (particles[i].pos + ATS(settings->emission_point_minimal) + offsets[i])).magnitude() > 
			settings->max_distance_to_middle && settings->max_distance_to_middle != 0.f) {
			Vec2f dir(sur::Direction(settings->middle, STA(particles[i].pos) + settings->emission_point_minimal + STA(offsets[i])));
			offsets[i] = offsets[i] + Vec2(static_cast<i32>(ceil(dir.x * noise * 3)), static_cast<i32>(ceil(dir.y * noise * 3)));
			continue;
		}
		if (std::find(settings->blocked_directions.begin(), settings->blocked_directions.end(), ParticleDirection::North) == settings->blocked_directions.end() && dir == 0) {
			offsets[i].y -= noise; 															
		}
		if (std::find(settings->blocked_directions.begin(), settings->blocked_directions.end(), ParticleDirection::North_East) == settings->blocked_directions.end() && dir == 1) {
			offsets[i].x -= noise; 
			offsets[i].y -= noise;
		}
		if (std::find(settings->blocked_directions.begin(), settings->blocked_directions.end(), ParticleDirection::East) == settings->blocked_directions.end() && dir == 2) {
			offsets[i].x -= noise;														
		}
		if (std::find(settings->blocked_directions.begin(), settings->blocked_directions.end(), ParticleDirection::South_East) == settings->blocked_directions.end() && dir == 3) {
			offsets[i].y += noise; 
			offsets[i].x -= noise;
		}
		if (std::find(settings->blocked_directions.begin(), settings->blocked_directions.end(), ParticleDirection::South) == settings->blocked_directions.end() && dir == 4) {
			offsets[i].y += noise; 
		}
		if (std::find(settings->blocked_directions.begin(), settings->blocked_directions.end(), ParticleDirection::South_West) == settings->blocked_directions.end() && dir == 5) {
			offsets[i].y += noise;
			offsets[i].x += noise;
		}
		if (std::find(settings->blocked_directions.begin(), settings->blocked_directions.end(), ParticleDirection::West) == settings->blocked_directions.end() && dir == 6) {
			offsets[i].x += noise;
		}
		if (std::find(settings->blocked_directions.begin(), settings->blocked_directions.end(), ParticleDirection::North_West) == settings->blocked_directions.end() && dir == 7) {
			offsets[i].y -= noise;
			offsets[i].x += noise;
		}
	}
	for (i32 i = 0; i < particles.size(); ++i)
		Set(particles[i].pos + ATS(settings->emission_point_minimal) + offsets[i], particles[i].color);
}

