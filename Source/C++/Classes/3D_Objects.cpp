

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
	: points(other->points), color(color), origin(origin), projection(projection) {}


struct Mat4x4
{
	f32 m[4][4] = { 0 };
};

sur::Vec3f Mat4x4MulVec3f(const sur::Vec3f& vec, Mat4x4 mat) {
	sur::Vec3f tmp;
	tmp.x = vec.x * mat.m[0][0] + vec.y * mat.m[1][0] + vec.z * mat.m[2][0] + mat.m[3][0];
	tmp.y = vec.x * mat.m[0][1] + vec.y * mat.m[1][1] + vec.z * mat.m[2][1] + mat.m[3][1];
	tmp.z = vec.x * mat.m[0][2] + vec.y * mat.m[1][2] + vec.z * mat.m[2][2] + mat.m[3][2];
	f32 w = vec.x * mat.m[0][3] + vec.y * mat.m[1][3] + vec.z * mat.m[2][3] + mat.m[3][3];
	if (w != 0.f) {
		tmp.x /= w; tmp.y /= w; tmp.z /= w;
	}
	return tmp;
}

void sur::Cuboid::Rotate(Dimension dimension, i32 angle) {
	switch (dimension)
	{
	case Dimension::X: angleX = angle; break;
	case Dimension::Y: angleY = angle; break;
	case Dimension::Z: angleZ = angle; break;
	}
}

void sur::Cuboid::Bind(bool Render, i32 perspectiveThreshold) {
	std::vector<Vec2f> transformed;
	for (auto&& iter : points) {
		Vec3f tmp = iter;
		tmp = sur::RotateX(tmp, origin - offset, angleX);
		tmp = sur::RotateY(tmp, origin - offset, angleY);
		tmp = sur::RotateZ(tmp, origin - offset, angleZ);
		Mat4x4 matProj;
		if (perspectiveThreshold != 0) {
			f32 fNear = 0.1f;
			f32 fFar = 1000.0f;
			f32 fFov = 90.0f;
			f32 fAspectRatio = (f32)_window_size.y / (f32)_window_size.x;
			f32 fFovRad = 1.0f / tanf(fFov * 0.5f / 180.0f * PI);	
			matProj.m[0][0] = fAspectRatio * fFovRad;
			matProj.m[1][1] = fFovRad;
			matProj.m[2][2] = fFar / (fFar - fNear);
			matProj.m[3][2] = (-fFar * fNear) / (fFar - fNear);
			matProj.m[2][3] = 1.0f;
			matProj.m[3][3] = 0.0f;

		}
		Vec3f projectedPoint = Mat4x4MulVec3f(tmp, matProj);
		transformed.push_back(projectedPoint.toVec2f() + offset.toVec2f());
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

//if (perspectiveThreshold != 0) {
//	f32 z = 0;
//	/*if (tmp.z + offset.z == 0) z = 1;
//	else*/ z = 1 / (tmp.z + offset.z);
//	projection
//	(
//		z, 0, 0,
//		0, z, 0,
//		0, 0, 1
//	);
//}
/*Vec3f projectedPoint = projection.multiplyWithVector(tmp);*/
void sur::Cuboid::Move(Vec3f direction){
	origin = origin + direction;
	for (auto&& iter : points) {
		iter = iter + direction;
	}
}
