

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
		while (local_position == ATS(settings->middle)) {
			local_position(
				sur::RandomRange(0, Pixel(settings->emission_point_maximal.x - settings->emission_point_minimal.x)),
				sur::RandomRange(0, Pixel(settings->emission_point_maximal.y - settings->emission_point_minimal.y))
			);
		}
		Color color = settings->colors[static_cast<size_t>(sur::RandomRange(0, static_cast<i32>(settings->colors.size()) - 1))];
		particles.push_back({ local_position, color });
		offsets.push_back({ 0,0 });
	}
}

void sur::ParticleSystem::MoveTowards(Vec2f position, i32 moveQueueIndex, f32 minSpeed, f32 maxSpeed)
{
	i32 supportedThreads = std::thread::hardware_concurrency() == 0 ? 2 : std::thread::hardware_concurrency();
	constexpr i32 minDataPerThread = 1000;
	i32 maxAmountOfThread = ((i32)offsets.size() + minDataPerThread - 1) / minDataPerThread;
	i32 amountOfThreads = supportedThreads > maxAmountOfThread ? maxAmountOfThread : supportedThreads;

	i32 dataPerThread = (i32)offsets.size() / amountOfThreads;

	std::vector<std::thread> threads(amountOfThreads - 1); // - 1, because main thread will be used too

	auto calculate = [&](i32 start, i32 end)
	{
		for (i32 i = start; i < end; ++i)
		{
			Vec2f dir(sur::Direction(position, STA(particles[i].pos) + settings->emission_point_minimal + STA(offsets[i])));
			Vec2 move = particles[i].MoveQueue(
				dir * static_cast<f32>(sur::RandomRange(static_cast<i32>(minSpeed), static_cast<i32>(maxSpeed))), moveQueueIndex
			);
			if (move.x == 0 && move.y == 0)
				continue;
			offsets[i] += move;
		}
	};
	for (i32 i = 0; i < amountOfThreads - 1; ++i)
		threads[i] = std::thread(calculate, dataPerThread * i, dataPerThread * (i + 1));

	i32 startOffset = dataPerThread * (amountOfThreads - 1);
	calculate(startOffset, static_cast<i32>(particles.size()));

	for (i32 i = 0; i < amountOfThreads - 1; ++i)
		threads[i].join();
}

void sur::ParticleSystem::Bind(bool render)
{
	for (i32 i = 0; i < offsets.size(); ++i) {
		bool l1 = false;
		bool l2 = false;
		i32 noise = sur::RandomRange(settings->min_noise, settings->max_noise);
		ParticleDirection dir = static_cast<ParticleDirection>(sur::RandomRange(0, 8));
		if (settings->prefered_directions.size() > 0) {
			bool makePrefered = sur::RandomRange(0, settings->prefered_directions_intensity) == 0 ? true : false;
			if (makePrefered) {
				dir = settings->prefered_directions[static_cast<size_t>(sur::RandomRange(0, static_cast<i32>(settings->prefered_directions.size()) - 1))];
			}
		}

		while ((ATS(settings->middle) - (particles[i].pos + ATS(settings->emission_point_minimal) + offsets[i])).magnitude() > 
			settings->max_distance_to_middle && settings->max_distance_to_middle != 0.f) {		
			l1 = true;
			Vec2f dir(sur::Direction(settings->middle, STA(particles[i].pos) + settings->emission_point_minimal + STA(offsets[i])));
			offsets[i] = offsets[i] + Vec2(static_cast<i32>(ceil(dir.x * noise * 2)), static_cast<i32>(ceil(dir.y * noise * 2)));
		}
		if (l1) continue;

		while ((ATS(settings->middle) - (particles[i].pos + ATS(settings->emission_point_minimal) + offsets[i])).magnitude() <
			settings->min_distance_to_middle && settings->min_distance_to_middle != 0.f) {
			l2 = true;
			Vec2f dir(sur::Direction(settings->middle, STA(particles[i].pos) + settings->emission_point_minimal + STA(offsets[i])) * -1);
			if (dir.x == 0 && dir.y == 0)
				dir.y = 1;
			offsets[i] = offsets[i] + Vec2(static_cast<i32>(ceil(dir.x * noise * 2)), static_cast<i32>(ceil(dir.y * noise * 2)));
		}
		if (l2) continue;

		if (std::find(settings->blocked_directions.begin(), settings->blocked_directions.end(), North) == settings->blocked_directions.end() && dir == North) {
			offsets[i].y += noise; 															
		}
		if (std::find(settings->blocked_directions.begin(), settings->blocked_directions.end(), North_East) == settings->blocked_directions.end() && dir == North_East) {
			offsets[i].x += noise; 
			offsets[i].y += noise;
		}
		if (std::find(settings->blocked_directions.begin(), settings->blocked_directions.end(), East) == settings->blocked_directions.end() && dir == East) {
			offsets[i].x += noise;														
		}
		if (std::find(settings->blocked_directions.begin(), settings->blocked_directions.end(), South_East) == settings->blocked_directions.end() && dir == South_East) {
			offsets[i].y -= noise; 
			offsets[i].x += noise;
		}
		if (std::find(settings->blocked_directions.begin(), settings->blocked_directions.end(), South) == settings->blocked_directions.end() && dir == South) {
			offsets[i].y -= noise; 
		}
		if (std::find(settings->blocked_directions.begin(), settings->blocked_directions.end(), South_West) == settings->blocked_directions.end() && dir == South_West) {
			offsets[i].y -= noise;
			offsets[i].x -= noise;
		}
		if (std::find(settings->blocked_directions.begin(), settings->blocked_directions.end(), West) == settings->blocked_directions.end() && dir == West) {
			offsets[i].x -= noise;
		}
		if (std::find(settings->blocked_directions.begin(), settings->blocked_directions.end(), North_West) == settings->blocked_directions.end() && dir == North_West) {
			offsets[i].y += noise;
			offsets[i].x -= noise;
		}
	}
	for (i32 i = 0; i < particles.size(); ++i)
		Set(particles[i].pos + ATS(settings->emission_point_minimal) + offsets[i], particles[i].color);
}


