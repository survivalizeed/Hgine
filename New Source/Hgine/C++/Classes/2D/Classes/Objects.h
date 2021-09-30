

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

	enum ParticleDirection
	{

		North,
		North_East,
		East,
		South_East,
		South,
		South_West,
		West,
		North_West

	};

	struct ParticleSettings 
	{

		i32 emission;
		i32 min_noise;
		i32 max_noise;	
		i32 prefered_directions_intensity;	// The higher, the lower the chance
		f32 min_distance_to_middle = 0;
		f32 max_distance_to_middle = 0;
		Vec2f origin;
		Vec2f middle;
		Vec2f emission_point_minimal;
		Vec2f emission_point_maximal;
		std::vector<ParticleDirection> blocked_directions;
		std::vector<ParticleDirection> prefered_directions;
		std::vector<Color> colors;

	};
//=======================================================================
	class Object 
	{
	protected:

		struct MoveQueueContainer {
			Vec2f counter_neg;
			Vec2f counter_pos;
			Vec2 counter_counter_neg = { 1, 1};
			Vec2 counter_counter_pos = { -1, -1 };
		};

		i32 hash;

		Type type;

		std::string name;

		std::map<i32, MoveQueueContainer> mvContainer;	

	public:
	
		bool active;
		Color color;
		Vec2f position;

		Vec2 MoveQueue(Vec2f direction, i32 moveQueueIndex);
		
		virtual Vec2 Move(Vec2f direction, i32 moveQueueIndex);

		std::string_view GetName();
	
		Type GetType();

		i32 GetHash();

	};
//=======================================================================
	struct Line : public Object
	{

		Vec2f start_point;
		Vec2f end_point;

		Line() = default;

		Line(Vec2f start_point, Vec2f end_point, Color color, std::string_view name);

		Vec2 Move(Vec2f direction, i32 moveQueueIndex) override;

		void Bind(bool render);

	};
//=======================================================================
	struct Triangle : public Object 
	{
		
		Vec2f p1, p2, p3;

		Triangle() = default;

		Triangle(Vec2f p1, Vec2f p2, Vec2f p3, Color color, std::string_view name);

		void SetPoint(u32 index, Vec2f position);

		Vec2f GetPoint(u32 index);

		Vec2 Move(Vec2f direction, i32 moveQueueIndex) override;

		void Bind(bool render, bool wireframe);

	};
//=======================================================================
	struct Form : public Object 
	{	
		
		std::vector<Vec2f> points;
		std::vector<i32> indices;

		enum class Modifier {
			None,
			InverseKinematic,
			ConvexHull	// not supported yet
		} modifier;

		enum class FillMode {
			Auto,
			Index
		} fillMode;

		Form() = default;

		//The indices are 3 grouped. Every 3 indices create a triangle. If the FillMode is Auto, you can put {} in the indices parameter
		Form(const std::vector<Vec2f>& points, const std::vector<i32>& indices, const Modifier& modifier, const FillMode& fillMode,
			Color color, std::string_view name);

		void SetPoint(u32 index, Vec2f position);

		Vec2f GetPoint(u32 index);

		void SetIndex(u32 index, i32 what);

		i32 GetIndex(u32 index);

		void Insert(u32 index, Vec2f position);

		void Remove(u32 index);

		Vec2 Move(Vec2f direction, i32 moveQueueIndex) override;

		void Bind(bool render, bool wireframe);

	};
//=======================================================================
	struct Square : public Object
	{

		Vec2f start_point;
		Vec2f end_point;

		Square() = default;

		Square(Vec2f start_point, Vec2f end_point, Color color, std::string_view name);

		void Bind(bool render);

	};
//=======================================================================
	class Sprite : public Object 
	{
	private:

		using Object::color;

		Vec2 size;

		void LoadHgineres(std::string_view path);

		void LoadPng(std::string_view path, Color colorToAlpha);

	public:

		std::vector<Vec2> points;
		std::vector<Color> colors;

		enum class FileType {
			Hgineres,
			PNG,
			Empty
		};

		Sprite() = default;

		// colorToAlpha not required for filetype Hgineres
		Sprite(std::string_view path, FileType filetype, Vec2f position, std::string_view name, Color colorToAlpha = Color(0,0,0));

		void Bind(bool render);

	};
//=======================================================================
	class ParticleSystem
	{
	private:

		struct Particle : public Object
		{
			Vec2 pos;
			Color color;
			Particle() = default;
			Particle(Vec2 pos, Color color) : pos(pos), color(color) {}
		};

		std::vector<Particle> particles;
		std::vector<Vec2> offsets;
		ParticleSettings* settings;

	public:

		ParticleSystem() = default;

		ParticleSystem(ParticleSettings* settings);

		void MoveTowards(Vec2f position, i32 moveQueueIndex, f32 minSpeed, f32 maxSpeed);

		void Bind(bool render);
		
	};
}