

#include "3D_Objects.h"
#include "../Functional/functional.h"
#include "../Functional/TemporaryObjects.h"


sur::Cuboid::Cuboid(Vec3f a, Vec3f b, Vec3f c, Vec3f d, Vec3f e, Vec3f f, Vec3f g, Vec3f h, Color color, Vec3f origin,
	const Mat3x3& projection) : color(color), origin(origin), offset(origin), projection(projection)
{
	points[0] = a - offset;
	points[1] = b - offset;
	points[2] = c - offset;
	points[3] = d - offset;
	points[4] = e - offset;
	points[5] = f - offset;
	points[6] = g - offset;
	points[7] = h - offset;
}

sur::Cuboid::Cuboid(const Cuboid* const other, Color color, Vec3f origin, const Mat3x3& projection)
	: points(other->points),color(color), origin(origin), projection(projection) {}


void sur::Cuboid::Rotate(Dimension dimension, i32 angle){
	switch (dimension)
	{
	case Dimension::X: angleX = angle; break;
	case Dimension::Y: angleY = angle; break;
	case Dimension::Z: angleZ = angle; break;
	}
}

void sur::Cuboid::Bind(bool Render, i32 perspectiveThreshold){
	std::vector<Vec2> transformed;
	for (auto&& iter : points) {
		Vec3f tmp = iter;
		tmp = sur::RotateX(tmp, origin - offset, angleX);
		tmp = sur::RotateY(tmp, origin - offset, angleY);
		tmp = sur::RotateZ(tmp, origin - offset, angleZ);		
		if (perspectiveThreshold != 0) {
			f32 z = 1 / (tmp.z + offset.z);
			z *= 160.f;
			if (z > 3.f) z = 3.f;
			projection
			(
				z, 0, 0,
				0, z, 0,
				0, 0, 0
			);
		}
		Vec3f projectedPoint = projection.multiplyWithVector(tmp);
		transformed.push_back(projectedPoint.toVec2() + offset.toVec2());
	}

	{
		sur::TMP::Line(transformed[0], transformed[1], color);
		sur::TMP::Line(transformed[1], transformed[2], color);
		sur::TMP::Line(transformed[2], transformed[3], color);
		sur::TMP::Line(transformed[3], transformed[0], color);

		sur::TMP::Line(transformed[0], transformed[4], color);
		sur::TMP::Line(transformed[1], transformed[5], color);
		sur::TMP::Line(transformed[2], transformed[6], color);
		sur::TMP::Line(transformed[3], transformed[7], color);

		sur::TMP::Line(transformed[4], transformed[5], color);
		sur::TMP::Line(transformed[5], transformed[6], color);
		sur::TMP::Line(transformed[6], transformed[7], color);
		sur::TMP::Line(transformed[7], transformed[4], color);
	}
	transformed.clear();
}

void sur::Cuboid::Move(Vec3f direction){
	
}
