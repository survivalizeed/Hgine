#pragma once

#include "../../../../Includes.h"

namespace sur
{
	class Input;
	class Object;


	enum class Type
	{

		Square,
		Line,
		Triangle,
		Form,
		Sprite,
		ParticleSystem,
		Light,
		Font,
		Text,
		Camera

	};

	enum class ColliderType
	{

		None,
		AABB,
		SAT  // Not supported yet

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
		Vec2f emission_point_minimal;
		Vec2f emission_point_maximal;
		std::vector<ParticleDirection> blocked_directions;
		std::vector<ParticleDirection> prefered_directions;
		std::vector<Color> colors;

	};
	//=======================================================================
	class MvQ
	{
	protected:

		struct MoveQueueContainer {
			Vec2f counter_neg;
			Vec2f counter_pos;
			Vec2 counter_counter_neg = { 1, 1 };
			Vec2 counter_counter_pos = { -1, -1 };
		};

		std::map<i32, MoveQueueContainer> mvContainer;

	public:

		Vec2 MoveQueue(Vec2f direction, i32 moveQueueIndex);

	};
//=======================================================================
	class BoxHover
	{
	private:

		Input* input1;
		Input* input2;
		Input* input3;

		bool previousHover = false;
		bool hover;

		Object* objectToAttachTo = nullptr;

	public:

		Vec2f start;
		Vec2f end;

		BoxHover() = default;

		BoxHover(Object* objectToAttachTo, Vec2f start, Vec2f end);

		cb_ptr_s<Object*> onNotHover = nullptr;
				 
		cb_ptr_s<Object*> onHoverEnter = nullptr;
		cb_ptr_s<Object*> onHoverStay = nullptr;
		cb_ptr_s<Object*> onHoverExit = nullptr;
				 
		cb_ptr_s<Object*> onHoverLClickHeld = nullptr;
		cb_ptr_s<Object*> onHoverRClickHeld = nullptr;
		cb_ptr_s<Object*> onHoverLClickPress = nullptr;
		cb_ptr_s<Object*> onHoverRClickPress = nullptr;
		cb_ptr_s<Object*> onHoverLClickRelease = nullptr;
		cb_ptr_s<Object*> onHoverRClickRelease = nullptr;
				 
		cb_ptr_s<Object*> onNotHoverLClickHeld = nullptr;
		cb_ptr_s<Object*> onNotHoverRClickHeld = nullptr;
		cb_ptr_s<Object*> onNotHoverLClickPress = nullptr;
		cb_ptr_s<Object*> onNotHoverRClickPress = nullptr;
		cb_ptr_s<Object*> onNotHoverLClickRelease = nullptr;
		cb_ptr_s<Object*> onNotHoverRClickRelease = nullptr;
				 
		cb_ptr_s<Object*> onLClickHeld = nullptr;
		cb_ptr_s<Object*> onRClickHeld = nullptr;
		cb_ptr_s<Object*> onLClickPress = nullptr;
		cb_ptr_s<Object*> onRClickPress = nullptr;
		cb_ptr_s<Object*> onLClickRelease = nullptr;
		cb_ptr_s<Object*> onRClickRelease = nullptr;

		void CheckHover();

		~BoxHover();

	};
//=======================================================================
	class Collider
	{
	protected:

		std::vector<bool> previousCall;
		std::vector<bool> collided;

		Object* objectToAttachTo = nullptr;

	public:

		Vec2f start;
		Vec2f end;

		ColliderType colliderType;

		Collider() = default;

		Collider(Object* objectToAttachTo, Vec2f start, Vec2f end, ColliderType colliderType);

		bool anyCollisionLeft = false;

		cb_ptr<Object*> onCollisionEnter = nullptr;

		cb_ptr<Object*> onCollisionStay = nullptr;

		cb_ptr<Object*> onCollisionExit = nullptr;

		void CheckCollision();

		Vec2 Move(sur::Object* current, Vec2 incomingDirection);

	};
//=======================================================================
	class Object : public MvQ
	{
	protected:

		i32 hash;
		Type type;
		std::string name;

		Vec2f original_position;

		void DoRelevantChecks();

	public:

		bool childOfCamera = false;
		bool active = true;
		Color color;

		Vec2f position;

		BoxHover* boxHover = nullptr;
		Collider* collider = nullptr;		
		
		std::string_view GetName() const;

		Type GetType() const;

		i32 GetHash() const;

		Vec2f GetOriginalPosition() const;

		virtual Vec2 Move(Vec2f direction, i32 moveQueueIndex);

		~Object();

	};
//=======================================================================
	struct Line : public Object
	{

		Vec2f start_point;
		Vec2f end_point;

		Line() = default;

		Line(Vec2f start_point, Vec2f end_point, Color color, std::string_view name);

		void Bind(bool render);

	};
//=======================================================================
	struct Triangle : public Object
	{

		Vec2f p1, p2, p3;

		Triangle() = default;

		Triangle(Vec2f p1, Vec2f p2, Vec2f p3, Color color, std::string_view name);

		void SetPoint(u32 index, Vec2f position);

		Vec2f GetPoint(u32 index) const;

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
			ConvexHull	// Not supported yet
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

		Vec2f GetPoint(u32 index) const;

		void SetIndex(u32 index, i32 what);

		i32 GetIndex(u32 index) const;

		void Insert(u32 index, Vec2f position);

		void Remove(u32 index);

		void Bind(bool render, bool wireframe);

	};
//=======================================================================
	class Square : public Object
	{
	private:

		bool CheckOutOfScreen();

	public:

		Vec2f start_point;
		Vec2f end_point;

		Square() = default;

		Square(Vec2f start_point, Vec2f end_point, Color color, std::string_view name);

		void Bind(bool render);

	};
	//=======================================================================
	class Sprite : public Object
	{
	protected:

		Vec2f scaleOrigin;
		Mat3x3 scale = Mat3x3(1, 0, 0, 0, 1, 0, 0, 0, 1);

		using Object::color;

		void LoadHgineres(std::string_view path);

		void LoadPng(std::string_view path, Color colorToAlpha);

		bool CheckOutOfScreen();

		Color TintPixel(Color color);

	public:

		Vec2f size;		// This can variate if you for example scale the sprite
		Vec2f original_size;

		H_RGB tint;
		std::vector<Vec2> points;
		std::vector<Color> colors;

		enum class FileType {
			Hgineres,
			PNG,
			Empty
		};

		Sprite() = default;

		// colorToAlpha not required for filetype Hgineres
		Sprite(std::string_view file, FileType filetype, Vec2f position, std::string_view name, Color colorToAlpha = Color(0, 0, 0));

		void Scale(Vec2f scaleOrigin, Vec2f scale);

		void Bind(bool render);

	};
	//=======================================================================
	class ParticleSystem : public Object
	{
	private:

		struct Particle : public Object
		{
			Vec2 pos;
			Color color;
			Particle() = default;
			Particle(Vec2 pos, Color color) : pos(pos), color(color) {}
		};

		using Object::color;

		std::vector<Particle> particles;
		std::vector<Vec2> offsets;
		ParticleSettings* settings;

	public:

		ParticleSystem() = default;

		ParticleSystem(ParticleSettings* settings, std::string_view name);

		void MoveTowards(Vec2f position, i32 moveQueueIndex, f32 minSpeed, f32 maxSpeed);

		Vec2 Move(Vec2f direction, i32 moveQueueIndex);

		void Bind(bool render);

	};
	//=======================================================================
	class Light : public Object
	{
	public:

		f32 radius;
		f32 threshold;
		f32 falloffIntensity;

		Light() = default;

		Light(Vec2f position, f32 radius, f32 threshold, f32 falloffIntensity, Color color, std::string_view name);

		static Color LightPixel(Vec2 pos, Color color);

		void Bind();

	};
	//=======================================================================
	class Camera : private Object
	{
	public:

		Camera() = default;

		Camera(Vec2f position, bool active, std::string_view name);

		void MakeActive();

		void SetPosition(Vec2f position);

		Vec2f GetPosition();

		Object::GetName;

		Object::GetType;

		Object::GetHash;

		Vec2 Move(Vec2f direction, i32 moveQueueIndex) override;

		void Bind();

	};
//=======================================================================
}