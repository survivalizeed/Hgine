

#pragma once

#include "../../../../Includes.h"

namespace sur 
{
	enum ParticleDirection3D
	{

		Forward,
		Backward,
		Up,
		Down,
		Right,
		Left

	};

	struct ParticleSettings3D
	{

		i32 emission;
		i32 min_noise;
		i32 max_noise;
		f32 min_distance_to_middle = 0;
		f32 max_distance_to_middle = 0;
		Vec3f origin;
		Vec3f middle;
		Vec3f emission_point_minimal;
		Vec3f emission_point_maximal;
		std::vector<Color> colors;

	};

	class ParticleSystem3D
	{
	private:

		struct Particle
		{
			Vec3f pos;
			Color color;
			Particle() = default;
			Particle(Vec3f pos, Color color) : pos(pos), color(color) {}
		};

		std::vector<Particle> particles;
		std::vector<Vec3f> offsets;
		ParticleSettings3D* settings;

	public:

		i32 angleX = 0, angleY = 0, angleZ = 0;

		Vec3f origin;
		Mat3x3 projection;

		ParticleSystem3D() = default;

		ParticleSystem3D(ParticleSettings3D* settings);

		void Rotate(Dimension dimension, i32 angle);

		void Move(Vec3f direction);

		void Bind(bool render, i32 perspectiveThreshold = 0, i32 clipping = 40);

	};
}
