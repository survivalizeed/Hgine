

#pragma once

#include "../../../Includes.h"

namespace sur 
{
	void hgineInitialize(Vec2 window_size, Vec2 aspect_ratio, std::string_view resource_path, std::string_view sound_path);

	void PlayWAV(const std::string& path, u32 params, i32 volume);

	void SetVolume(i32 volume);

	i64 GetMilliseconds();

	i32 RandomRange(i32 min, i32 max);

	void Set(Vec2 pos, Color color);

	Color Get(Vec2 pos);

	void SetLayer(Object* obj, i32 layer);

	Vec2f Absolute(Vec2f vec);

	f32 Distance(f32 first, f32 second);

	Vec2f Rotate2D(Vec2f position, Vec2f origin, i32 angle);

	Vec2f CalculateOrigin(const std::vector<Vec2f>& points);

	Vec2f Direction(Vec2f first, Vec2f second);

	Vec2f GetGeometryMetricsStart(Object* object);

	Vec2f GetGeometryMetricsEnd(Object* object);

	std::string GetExeDirectory();
	
	std::string GetClipBoardContent();

	std::vector<std::string> GetDirectoryFiles(std::string_view path);


	struct TriangleContainer;

	Vec3f CalculateOrigin3D(const std::vector<Vec3f>& points);

	std::vector<Vec3f> MeshTriangleContainerToVec3fs(const std::vector<TriangleContainer>& container);

	Vec3f Direction3D(Vec3f first, Vec3f second);

	Vec3f RotateX(Vec3f vec, Vec3f origin, i32 angle);
	
	Vec3f RotateY(Vec3f vec, Vec3f origin, i32 angle);
	
	Vec3f RotateZ(Vec3f vec, Vec3f origin, i32 angle);
	
}