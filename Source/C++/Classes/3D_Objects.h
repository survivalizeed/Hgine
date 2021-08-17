

#pragma once

#include "../Functional/includes.h"


// This Entire File (and the .cpp File) are still under development.


namespace sur {
	
	class Triangle;

	class Cuboid {
	private:
		i32 angleX = 0, angleY = 0, angleZ = 0;
		Color color;
		std::array<Vec3f, 8> points;

	public:
		Vec3f origin = { 0,0,0 };
		Mat3x3 projection;
		//------H#######G
		//----#-|------#|
		//--#---|----#--|		This was meant to show how the engine will interpret the given vectors :|
		//D#####E##C####F
		//|--------|-#
		//A########B 
		Cuboid(Vec3f a, Vec3f b, Vec3f c, Vec3f d, Vec3f e, Vec3f f, Vec3f g, Vec3f h, Color color, Vec3f origin,
			const Mat3x3& projection = { 1,0,0,0,1,0,0,0,0 });

		Cuboid(const Cuboid* const other, Color color, Vec3f origin, const Mat3x3& projection = { 1,0,0,0,1,0,0,0,0 });

		void Rotate(Dimension dimension, i32 angle);

		//A threshold around 120 is good ;)
		void Bind(bool Render, i32 perspectiveThreshold = 0);

		void Move(Vec3f direction);
	};

	class Mesh {
	private:
		i32 angleX = 0, angleY = 0, angleZ = 0;
		Color color;

		struct TriangleContainer {
			Vec3f a, b, c;
		};

		std::vector<TriangleContainer> triCon;

		std::vector<sur::Triangle> triangles;

	public:
		Vec3f origin = { 0,0,0 };
		Vec3f position;
		Mat3x3 projection;

		Mesh(const std::string& file, Vec3f position, Color color, Vec3f origin, const Mat3x3& projection = { 1,0,0,0,1,0,0,0,0 });

		void Rotate(Dimension dimension, i32 angle);

		void Bind(bool Render, i32 perspectiveThreshold = 0);

		void Move(Vec3f direction);
	};

}