

#pragma once

#include "../../../../Includes.h"


namespace sur
{
	struct TriangleContainer
	{	// Because the normal triangle can't hold 3d vectors

		Vec3f a;
		Vec3f b;
		Vec3f c;

	};

	struct Mesh 
	{

		i32 angleX = 0, angleY = 0, angleZ = 0;

		std::vector<TriangleContainer> triCon;

		Vec3f origin;
		Vec3f position;
		Mat3x3 projection;
		Color color;

		Mesh() = default;

		Mesh(const std::string& file, Vec3f position, Color color, Vec3f origin, const Mat3x3& projection = { 1,0,0,0,1,0,0,0,0 });

		void Rotate(Dimension dimension, i32 angle);

		void Move(Vec3f direction);

		void Bind(bool render, bool wireframe, i32 perspectiveThreshold = 0, i32 clipping = 40);

	};
}