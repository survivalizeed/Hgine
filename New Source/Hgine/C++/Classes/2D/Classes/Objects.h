

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
//=======================================================================
	class Object 
	{
	protected:

		std::string name;

	public:

		Type type;
		bool active;
		Color color;
		Vec2f position;
		i32 hash;

		std::string_view GetName()
		{
			return name;
		}

	};
//=======================================================================
	struct Line : public Object
	{

		Vec2f start_point;
		Vec2f end_point;

		Line(Vec2f start_point, Vec2f end_point, Color color, std::string_view name);

		void Bind(bool render);

	};
//=======================================================================
	struct Triangle : public Object 
	{
		
		Vec2f p1;
		Vec2f p2;
		Vec2f p3;

		Triangle(Vec2f p1, Vec2f p2, Vec2f p3, Color color, std::string_view name);

		void SetPoint(u32 index, Vec2f position);

		Vec2f GetPoint(u32 index);

		void Bind(bool render, bool wireframe);

	};
//=======================================================================
	struct Form : public Object 
	{	
		
		std::vector<Vec2f> points;

		enum class Modifier {
			None,
			InverseKinematic,
			ConvexHull	// not supported yet
		} modifier;

		Form(const std::vector<Vec2f>& points, const Modifier& modifier, Color color, std::string_view name);

		void SetPoint(u32 index, Vec2f position);

		Vec2f GetPoint(u32 index);

		void Insert(u32 index, Vec2f position);

		void Remove(u32 index);

		void Bind(bool render, bool wireframe);

	};
//=======================================================================
	struct Square : public Object
	{

		Vec2f start_point;
		Vec2f end_point;

		Square(Vec2f start_point, Vec2f end_point, Color color, std::string_view name);

		void Bind(bool render);
	
	};
//=======================================================================
	class Sprite : public Object 
	{
	private:

		using Object::color;

		Vec2 size;
		std::vector<Vec2> points;
		std::vector<Color> colors;

		void LoadHgineres(std::string_view path);

		void LoadPng(std::string_view path);

	public:

		enum class FileType {
			Hgineres,
			PNG
		};

		Sprite(std::string_view path, FileType filetype, Vec2f position, std::string_view name);

		void Bind(bool render);

	};

}