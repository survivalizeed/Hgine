

#pragma once

#include "../../../../Includes.h"

namespace sur
{
	enum class Type 
	{

		Rectangle,
		Line,
		Triangle,
		Form,
		Sprite,

	};

	struct Object 
	{
		
		Type type;
		bool active;
		Color color;
		Vec2f position;
		std::string name;

	};

	class Line : public Object
	{
	private:

		Vec2f start_point;
		Vec2f end_point;

	public:

		Line(Vec2f start_point, Vec2f end_point, Color color, std::string_view name);

		void SetStart(Vec2f start_point);

		void SetEnd(Vec2f end_point);

		Vec2f GetStart();
		
		Vec2f GetEnd();

		void Bind(bool render);

	};

	class Triangle : public Object 
	{
	private:
		
		Vec2f p1;
		Vec2f p2;
		Vec2f p3;

	public:

		Triangle(Vec2f p1, Vec2f p2, Vec2f p3, Color color, std::string_view name);

		void SetPoint(u32 index, Vec2f position);

		Vec2f GetPoint(u32 index);

		void Bind(bool render, bool wireframe);

	};

	class Form : public Object 
	{
	private:
		
		std::vector<Vec2f> points;

	public:

		Form(const std::vector<Vec2f>& points, Color color, std::string_view name);

		void SetPoint(u32 index, Vec2f position, bool inverseKinematic);

		Vec2f GetPoint(u32 index);

		void Bind(bool render, bool wireframe);

	};

	class Sprite : public Object 
	{
	private:

		using Object::color;

		Vec2 size;
		std::vector<Vec2> points;
		std::vector<Color> colors;

	public:

		Sprite(std::string_view path, Vec2f position, std::string_view name);

		void Bind(bool render);

	};

}