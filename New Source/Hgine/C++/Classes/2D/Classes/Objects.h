

#pragma once

#include "../../../../Includes.h"

namespace sur
{
	enum class Type 
	{

		Square,
		Line,
		Triangle,
		Form,
		Sprite,
		ParticleSystem,
		Light

	};

	enum class Collider
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
	class Object : public MvQ
	{
	protected:

		i32 hash;
		Type type;
		std::string name;
			
		Vec2f original_position;

	public:
	
		bool childOfCamera;
		bool active;
		Color color;
		
		Vec2f position;

		std::string_view GetName() const;
	
		Type GetType() const;

		i32 GetHash() const;

		Vec2f GetVirtualPosition() const;

		virtual void Bind(bool render) {};

	};
//=======================================================================
	class GameObject : public Object
	{
	protected:

		std::vector<bool> previousCall;
		std::vector<bool> collided;

		void AABBmove(GameObject* current, Vec2 incomingDirection);

		void CheckCollision();

		virtual bool CheckOutOfScreen() = 0;

	public:

		Collider collider;

		bool anyCollisionLeft = false;

		cb_ptr<GameObject*> onCollisionEnter;											
		cb_ptr<GameObject*> onCollisionStay;
		cb_ptr<GameObject*> onCollisionExit;

		Vec2 Move(Vec2f direction, i32 moveQueueIndex);

	};
//=======================================================================
	struct Line : public Object
	{

		Vec2f start_point;
		Vec2f end_point;

		Line() = default;

		Line(Vec2f start_point, Vec2f end_point, Color color, std::string_view name);

		Vec2 Move(Vec2f direction, i32 moveQueueIndex);

		void Bind(bool render) final;

	};
//=======================================================================
	struct Triangle : public Object 
	{
		
		Vec2f p1, p2, p3;

		Triangle() = default;

		Triangle(Vec2f p1, Vec2f p2, Vec2f p3, Color color, std::string_view name);

		void SetPoint(u32 index, Vec2f position);

		Vec2f GetPoint(u32 index) const;

		Vec2 Move(Vec2f direction, i32 moveQueueIndex);

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

		Vec2 Move(Vec2f direction, i32 moveQueueIndex);

		void Bind(bool render, bool wireframe);

	};
//=======================================================================
	class Square : public GameObject
	{
	private:

		bool CheckOutOfScreen() final;

	public:

		Vec2f start_point;
		Vec2f end_point;

		Square() = default;

		Square(Vec2f start_point, Vec2f end_point, Color color, Collider collider, std::string_view name);

		void Bind(bool render) final;

	};
//=======================================================================
	class Sprite : public GameObject 
	{
	protected:

		Vec2f scaleOrigin;
		Mat3x3 scale = Mat3x3(1, 0, 0, 0, 1, 0, 0, 0, 1);

		using Object::color;

		void LoadHgineres(std::string_view path);

		void LoadPng(std::string_view path, Color colorToAlpha);

		bool CheckOutOfScreen() final;

	public:

		Vec2f size;		// This can variate if you for example scale the sprite
		Vec2f original_size;

		std::vector<Vec2> points;
		std::vector<Color> colors;

		enum class FileType {
			Hgineres,
			PNG,
			Empty
		};

		Sprite() = default;

		// colorToAlpha not required for filetype Hgineres
		Sprite(std::string_view file, FileType filetype, Vec2f position, Collider colliderType, std::string_view name, Color colorToAlpha = Color(0,0,0));

		void Scale(Vec2f scaleOrigin, Vec2f scale);

		virtual void Bind(bool render) override;

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

		void Bind(bool render) final;
		
	};
//=======================================================================
	class Light : public Object
	{
	private:

		using Object::Bind;

	public:

		f32 radius;
		f32 threshold;
		f32 falloffIntensity;

		Light() = default;

		Light(Vec2f position, f32 radius, f32 threshold, f32 falloffIntensity, Color color, std::string_view name);

		static Color LightPixel(Vec2 pos, Color color);

		Vec2 Move(Vec2f direction, i32 moveQueueIndex);

	};
//=======================================================================
	class Camera : public MvQ
	{
	private:

		Vec2f position;
		
	public:

		Camera() = default;

		Camera(Vec2f position, bool active);

		void MakeActive();

		void SetPosition(Vec2f position);

		Vec2f GetPosition();

		Vec2 Move(Vec2f direction, i32 moveQueueIndex);

	};
//=======================================================================
	class Font {
	private:

		Sprite all;

	public:

		std::string align;

		std::vector<Sprite> chars;

		Font() = default;

		Font(std::string_view file, i32 charCount, std::string_view align, Color colorToAlpha);
		
		void OffsetChar(char character, Vec2 offset);

	};
//=======================================================================
	class Text
	{
	private:

		Vec2f original_position;

	public:

		i32 spacingX;
		i32 original_spacingX;

		Vec2f position;
		std::string text;
		Font* font;

		Text() = default;
	
		Text(Font* font, Vec2f position, i32 spacingX, std::string_view text);

		void Scale(f32 intensity);

		Vec2f GetVirtualPosition();

		void Bind(bool render);
	};
//=======================================================================
	class Button : public Sprite
	{
	private:

		bool previousHover = false;
		bool hover;

	public:

		using Sprite::Sprite;

		cb_ptr_s<Button*> OnMouseHoverEnter;

		cb_ptr_s<Button*> OnMouseHover;

		cb_ptr_s<Button*> OnMouseHoverExit;

		cb_ptr_s<Button*> OnMouseLClick;

		cb_ptr_s<Button*> OnMouseRClick;

		void Bind(bool render) final;

	};
}