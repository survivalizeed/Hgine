

#include "ParticleSystem3D.h"

sur::ParticleSystem3D::ParticleSystem3D(ParticleSettings3D* settings)
{
	this->settings = settings;
	settings->middle(
		f32(settings->emission_point_minimal.x + 0.5f * (settings->emission_point_maximal.x - settings->emission_point_minimal.x)),
		f32(settings->emission_point_minimal.y + 0.5f * (settings->emission_point_maximal.y - settings->emission_point_minimal.y)),
		f32(settings->emission_point_minimal.z + 0.5f * (settings->emission_point_maximal.z - settings->emission_point_minimal.z))
	);
	for (i32 i = 0; i < settings->emission; ++i) {
		Vec3f local_position(
			static_cast<f32>(RandomRange(0, static_cast<i32>(settings->emission_point_maximal.x - settings->emission_point_minimal.x))),
			static_cast<f32>(RandomRange(0, static_cast<i32>(settings->emission_point_maximal.y - settings->emission_point_minimal.y))),
			static_cast<f32>(RandomRange(0, static_cast<i32>(settings->emission_point_maximal.z - settings->emission_point_minimal.z)))
		);
		while (local_position == settings->middle) {
			local_position(
				static_cast<f32>(RandomRange(0, static_cast<i32>(settings->emission_point_maximal.x - settings->emission_point_minimal.x))),
				static_cast<f32>(RandomRange(0, static_cast<i32>(settings->emission_point_maximal.y - settings->emission_point_minimal.y))),
				static_cast<f32>(RandomRange(0, static_cast<i32>(settings->emission_point_maximal.z - settings->emission_point_minimal.z)))
			);
		}
		Color color = settings->colors[static_cast<size_t>(RandomRange(0, static_cast<i32>(settings->colors.size()) - 1))];
		particles.push_back({ local_position, color });
		offsets.push_back({ 0,0,0 });
	}
}

void sur::ParticleSystem3D::Rotate(Dimension dimension, i32 angle)
{
	switch (dimension)
	{
	case Dimension::X:
		angleX = angle;
		break;
	case Dimension::Y:
		angleY = angle;
		break;
	case Dimension::Z:
		angleZ = angle;
		break;
	}
}

void sur::ParticleSystem3D::Move(Vec3f direction)
{
	settings->middle += direction;
	for (auto& iter : offsets)
		iter += direction;
}

void sur::ParticleSystem3D::Bind(bool render, i32 perspectiveThreshold, i32 clipping)
{
	for (i32 i = 0; i < offsets.size(); ++i) {
		bool l1 = false;
		bool l2 = false;
		i32 noise = RandomRange(settings->min_noise, settings->max_noise);
		ParticleDirection3D dir = static_cast<ParticleDirection3D>(RandomRange(0, 6));

		while ((settings->middle - (particles[i].pos + settings->emission_point_minimal + offsets[i])).magnitude() >
			settings->max_distance_to_middle && settings->max_distance_to_middle != 0.f) {
			l1 = true;
			Vec3f dir(Direction3D(settings->middle, particles[i].pos + settings->emission_point_minimal + offsets[i]));
			offsets[i] = offsets[i] + Vec3f(
				static_cast<f32>(ceil(dir.x * noise * 2)), 
				static_cast<f32>(ceil(dir.y * noise * 2)),
				static_cast<f32>(ceil(dir.z * noise * 2)) 
			);
		}
		if (l1) continue;

		while ((settings->middle - (particles[i].pos + settings->emission_point_minimal + offsets[i])).magnitude() <
			settings->min_distance_to_middle && settings->min_distance_to_middle != 0.f) {
			l2 = true;
			Vec3f dir(Direction3D(settings->middle, particles[i].pos + settings->emission_point_minimal + offsets[i]) * -1);
			if (dir.x == 0 && dir.y == 0 && dir.z == 0)
				dir.y = 1;
			offsets[i] = offsets[i] + Vec3f(
				static_cast<f32>(ceil(dir.x * noise * 2)),
				static_cast<f32>(ceil(dir.y * noise * 2)),
				static_cast<f32>(ceil(dir.z * noise * 2))
			);
		}
		if (l2) continue;

		if (dir == Forward) {
			offsets[i].z++;
		}
		if (dir == Backward) {
			offsets[i].z--;
		}
		if (dir == Up) {
			offsets[i].y++;
		}
		if (dir == Down) {
			offsets[i].y--;
		}
		if (dir == Right) {
			offsets[i].x++;
		}
		if (dir == Left) {
			offsets[i].x--;
		}
	}
	std::vector<Vec3f> transformed;
	for (i32 i = 0; i < particles.size(); ++i) {
		Vec3f tmp(particles[i].pos + settings->emission_point_minimal + offsets[i] - settings->middle);
		tmp = RotateX(tmp, { 0,0,0 }, angleX);
		tmp = RotateY(tmp, { 0,0,0 }, angleY);
		tmp = RotateZ(tmp, { 0,0,0 }, angleZ);
		if (perspectiveThreshold != 0) {
			f32 z = 0;
			if (tmp.z + settings->middle.z == 0) z = 1;
			else z = 1 / ((tmp.z + settings->middle.z) / perspectiveThreshold);
			projection
			(
				z, 0, 0,
				0, z, 0,
				0, 0, 1
			);
		}
		Vec3f projectedPoint = projection.multiplyWithVector(tmp);
		if (projectedPoint.z + settings->middle.z > clipping) {
			transformed.push_back(projectedPoint + settings->middle);
		}
	}
	std::sort(transformed.begin(), transformed.end(), [](Vec3f& v1, Vec3f& v2) {
		return v1.z > v2.z;
		}
	);
	for (i32 i = 0; i < transformed.size(); ++i) {
		Set(transformed[i].toVec2(), particles[i].color);
	}
}

sur::Vec3f sur::ParticleSystem3D::Particle::MoveQueue(Vec3f direction)
{
	
}
