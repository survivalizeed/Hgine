

#pragma once

#include "../Functional/includes.h"

extern HWND _hwnd;
extern f32 _ambientLight;
extern bool _light;


namespace sur {
	//
	//	Classes
	//	 
	//
	//	Master: Defines the standard attributes of an object
	// Classes.cpp
	class Master {
	protected:

		std::vector<Vec2f> counterneg = { {-0.f,-0.f} };
		std::vector<Vec2f> counterpos = { {0.f,0.f} };
		std::vector<Vec2> countercountpos = { {1,1} };
		std::vector<Vec2> countercountneg = { {-1,-1 }};

		Color color;
		Vec2 moveiter;
		std::string name;
		Vec2 position;
		Vec2 size;

		std::vector<sur::Vec2> CollisionPos;
		std::vector<i32> push;


		Master(std::string_view name, i32 id, Color color, cb_ptr<Master*> callback = nullptr)
			: name(name), id(id), color(color), callback(callback) {}		//Line, Triangle

		Master(std::string_view name, i32 id, Vec2f position, cb_ptr<Master*> callback = nullptr)
			: name(name), id(id), position(ATS(position)), callback(callback) {}		//OBJ

		Master(std::string_view name, i32 id, Vec2f position, Vec2f size, cb_ptr<Master*> callback = nullptr)
			: name(name), id(id), position(ATS(position)), size(ATS(size)), callback(callback) {}		//Rectangle Trigger

		Master(std::string_view name, i32 id, Color color, Vec2f position, Vec2f size, cb_ptr<Master*> callback = nullptr)
			: name(name), id(id), color(color), position(ATS(position)), size(ATS(size)), callback(callback) {}		//Rectangle

		Vec2 rot(Vec2 pos, Vec2 origin, i32 Angle);	// The actual rotation math

		virtual inline void MoveInject(const Vec2& direction) { 
			position = position + direction; 
		}

	public:
		//Only used by the engine itself. Never use this!
		Vec2 MovQueue(Vec2f direction, i32 index);	// Handles floats and does nothing until a floating number becomes an integer

		Mat2x2 matrix = { 1, 0, 0, 1 };	//standard so it won't modify anything

		bool parentmem;

		enum class Type {
			Rectangle, Object, Triangle, Line, Shape, Trigger_Rectangle
		} type;

		std::vector<i32> ignore;

		//Don't use this variable
		bool active = true;

		i32 id;

		cb_ptr<Master*> callback = nullptr;

		Master() = default;

		inline std::string_view GetName() const { return name; }

		virtual inline void SetPosition(Vec2f position) { this->position = ATS(position); }

		virtual inline Vec2f GetPosition() const { return STA(position); }

		virtual inline Vec2f GetSize() const { return STA(size); }

		inline void SetColor(Color color) { this->color = color; }

		inline Vec2f GetOrigin() const { return GetPosition() + (GetSize() / 2); }

		inline bool State() const { return active; }

		virtual Vec2 Move(Vec2f direction, i32 MovQueueIndex, bool detect);
	};
	//
	//	Render class
	// Classes.cpp
	class Render {
	private:
		bool thread = false;
		volatile u32 frameCounter = 0;
		HDC dc;
		Color bg;
		bool fillBackground;
	public:

		Render(Color bg, bool fillBackground, f32 ambientLight, bool light) : bg(bg), fillBackground(fillBackground)
		{
			dc = GetDC(_hwnd);
			_ambientLight = ambientLight;
			_light = light;
		}

		void ClearScreenBuffer() const;

		void RenderScreenBuffer();

		void FPS();

		void DebugConsole(bool Show) const;
	};
	//
	//	Camera namespace <- no class because there will only be one
	// Classes.cpp
	namespace Camera {
		void Move(sur::Vec2f direction);
	};
	//
	//	Shape: Rectangle
	// Classes.cpp
	class Rectangle : public Master {
	private:

		inline void MoveInject(const Vec2& direction) override { position += direction; size += direction; }

	public:
		//Only use this if you want an array
		Rectangle() = default;

		Rectangle(Vec2f position, Vec2f size, Color color, std::string_view name, i32 id,
			const std::vector<i32>& ignoreids = { 0 }, const std::vector<i32>& push = { 0 }, cb_ptr<Master*> callback = nullptr);

		void Bind(bool Render, bool Collider);

	};
	//
	//	Load objects that were created with the Hgineres editor
	// LoadObj.cpp
	class Object : public Master {
	private:
		//Deleted functions
		inline void SetColor(Color color) = delete;

	private:
		bool fliped_X = false;
		bool fliped_Y = false;
		i32 x = 0;
		i32 y = 0;
		std::string path;
		sRGB tint_by;

		std::vector<i32>* XCoords = new std::vector<i32>;
		std::vector<i32>* YCoords = new std::vector<i32>;
		std::vector<Color>* Colors = new std::vector<Color>;

		void Load();

	public:
		Vec2f origin;
		i32 angle = 0;

		//Only use this if you want an array
		Object() = default;

		Object(std::string_view path, Vec2f position, std::string_view name, i32 id, const std::vector<i32>& ignoreids = { 0 },
			const std::vector<i32>& push = { 0 }, cb_ptr<Master*> callback = nullptr);

		Object(const Object* const obj, Vec2f position, std::string_view name, i32 id, const std::vector<i32>& ignoreids = { 0 },
			const std::vector<i32>& push = { 0 }, cb_ptr<Master*> callback = nullptr);

		void Bind(bool Render, ColliderType collidertype);

		void ScrollBind(bool Render);

		inline void Scale(Vec2f scale = { 1.f,1.f }) { matrix(scale.x, 0, 0, scale.y); }

		// A little joke method
		void LSD();

		void FlipX(bool flip);

		void FlipY(bool flip);

		inline void SetTint(sRGB rgb_intensity) { tint_by = rgb_intensity; }

		inline sRGB GetTint() { return tint_by; }

		inline XYC GetBuf() { return { XCoords,YCoords,Colors }; }

		~Object() {
			if (!parentmem) {
				delete YCoords;
				delete XCoords;
				delete Colors;
			}
		}
	};
	//
	//	Shape: Procedual Line
	// Classes.cpp
	class Line : public Master {
	private:
		//Deleted functions
		inline Vec2f GetPosition() = delete;
		inline Vec2f GetSize() = delete;
		inline Vec2f GetOrigin() = delete;

	private:
		Vec2 start;
		Vec2 end;
		size_t lenght = 0;

		inline void MoveInject(const Vec2& direction) override { start += direction; end += direction; }
	public:
		//Only use this if you want an array
		Line() = default;

		Line(Vec2f start, Vec2f end, Color color, std::string_view name, i32 id, const std::vector<i32>& ignoreids = { 0 },
			cb_ptr<Master*> callback = nullptr);

		inline void Start(Vec2f start) { this->start = ATS(start); }

		inline void End(Vec2f end) { this->end = ATS(end); }

		inline Vec2f GetStart() const { return STA(start); }

		inline Vec2f GetEnd() const { return STA(end); }

		inline void SetColor(Color color) { this->color = color; }

		void Bind(bool Render, bool Collider);
	};
	//
	//	Shape: Triangle
	// Triangle.cpp
	class Triangle : public Master {
	private:
		Vec2 p1, p2, p3;

		struct LineVector {
			bool* check = new bool[3];
			LineVector() { memset(check, false, 3); }
			std::vector<Vec2>* Line1 = new std::vector<Vec2>;
			std::vector<Vec2>* Line2 = new std::vector<Vec2>;
			std::vector<Vec2>* Line3 = new std::vector<Vec2>;

			void clear();

			std::vector<Vec2>* get(i32 i);

			std::vector<Vec2>* getother();
		} linevector;

		void Line(Vec2 start, Vec2 end, std::vector<sur::Vec2>* line, bool Render, bool Collider);

		void Fill(LineVector& linevector);

		inline void MoveInject(const Vec2& direction) override {
			p1 += direction;
			p2 += direction;
			p3 += direction;
		}

	public:
		//Only use this if you want an array
		Triangle() = default;

		Triangle(Vec2f p1, Vec2f p2, Vec2f p3, Color color, std::string_view name, i32 id,
			const std::vector<i32>& ignoreids = { 0 }, cb_ptr<Master*> callback = nullptr);

		inline void SetPosition(i32 which, Vec2f pos) {
			switch (which) {
			case 0:
				p1 = ATS(pos);
				return;
			case 1:
				p2 = ATS(pos);
				return;
			case 2:
				p3 = ATS(pos);
				return;
			}
		}

		void Bind(bool Render, bool Collider);

		~Triangle() {
			delete linevector.Line1, linevector.Line2, linevector.Line3;
		}
	};
	//
	//	Shape: Custom wire shape
	// Classes.cpp
	class Shape : public Master {
	private:
		//Deleted attributes
		using Master::ignore;
		using Master::matrix;

		//Deleted functions
		inline Vec2f GetPosition() = delete;
		inline Vec2f GetSize() = delete;
		inline Vec2f GetOrigin() = delete;

	private:
		std::vector<Vec2>* vec = new std::vector<Vec2>;
		std::vector<Line*>* lines = new std::vector<Line*>;

		void Gen();

		template<VEC R>
		void Pass(R r) {
			vec->push_back((Vec2f)r);
			Gen();
		}

	public:
		//Only use this if you want an array
		Shape() = default;

		Shape(Color color, std::string_view name, i32 id, const std::vector<i32>& ignoreids = { 0 },
			cb_ptr<Master*> callback = nullptr);

		// Call after constructor
		template<VEC F, VEC ... R>
		void Pass(F f, R ... r) {
			vec->push_back((Vec2f)f);
			Pass(r...);
		}

		void SetPosition(i32 index, Vec2f position);

		void Bind(bool Render, bool Collider);

		void Move(Vec2f direction, i32 MovQueueIndex);
	};
	//
	//	Particle system
	// 
	class Particles : public Master {
	private:
		struct Particle : public Master {
			Vec2 pos;
			Color color;
			Particle() = default;
			Particle(Vec2 pos, Color color) : pos(pos), color(color) {}
		};

		std::vector<Particle>* Coords = new std::vector<Particle>;
		std::vector<Vec2>* Offsets = new std::vector<Vec2>;
		ParticlesSetting* settings;

		inline void MoveInject(const Vec2& direction) override { position += direction; }
	public:

		Particles() = default;

		Particles(ParticlesSetting* settings);

		//Moves every particle to the desired position.
		//Be careful it is very performance heavy!
		void MoveTowards(Vec2f position, i32 MovQueueIndex, f32 speed);

		void Bind(bool Render);

		//Only moves the particles
		inline void Move(Vec2f direction, i32 MovQueueIndex) cpar(Master::Move(direction, MovQueueIndex, false))

		//Moves the particles, the middle and everything else
		inline void MoveAll(Vec2f direction, i32 MovQueueIndex) {
			Vec2 newdirection = MovQueue(direction, MovQueueIndex);
			settings->middle = settings->middle + newdirection;
			position += newdirection;
		}
	};

	class Light : public Master {
	private:
		inline Vec2f GetOrigin() = delete;
		inline Vec2f GetSize() = delete;

	public:
		f32 radius;
		using Master::color;

		Light() = default;

		Light(Vec2f position, f32 radius, Color color, std::string_view name);

	};

	class Text : public Master {
	private:
		u32 size;

	public:

		std::string text;

		Text() = default;

		Text(std::string_view text, Vec2f position, Color color, u32 size)
			: text(text), size(size) {
			this->position = ATS(position);
			this->color = color;
		}

		void Bind(bool Render);
	};
	//
	//	Triggers
	// Classes_2.cpp
	namespace Triggers {
		class Rectangle : public Master
		{
		private:

		public:
			Rectangle(Vec2f position, Vec2f size, std::string_view name, i32 id, const std::vector<i32>& ignoreids = { 0 },
				cb_ptr<Master*> callback = nullptr);

			inline void Move(Vec2f direction, i32 MovQueueIndex) cpar(Master::Move(direction, MovQueueIndex, false))

			void Bind();
		};
	}
	//
	//	Instancer <- For object management
	// Instancer.cpp
	namespace Instancer {
		struct restricted {
			inline static std::vector<sur::Rectangle*>* rectangles = new std::vector<sur::Rectangle*>;
			inline static std::vector<sur::Line*>* lines = new std::vector<sur::Line*>;
			inline static std::vector<sur::Object*>* objects = new std::vector<sur::Object*>;
			inline static std::vector<sur::Triangle*>* triangles = new std::vector<sur::Triangle*>;
			inline static std::vector<sur::Shape*>* shapes = new std::vector<sur::Shape*>;
			inline static std::vector<sur::Triggers::Rectangle*>* trigger_rectangles = new std::vector<sur::Triggers::Rectangle*>;

			// To return if nothing was found -> prevent error of nullpointer
			inline static sur::Rectangle* Rdefault = new sur::Rectangle({ 0,0 }, { 0,0 }, Color(0, 0, 0), "invalid", -1);
			inline static sur::Line* Ldefault = new sur::Line({ 0,0 }, { 0,0 }, Color(0, 0, 0), "invalid", -1);
			inline static sur::Object* Odefault = new sur::Object("invalid", { 0,0 }, "invalid", -1);
			inline static sur::Triangle* Tdefault = new sur::Triangle({ 0,0 }, { 0,0 }, { 0,0 }, Color(0, 0, 0), "invalid", -1);
			inline static sur::Shape* Sdefault = new sur::Shape(Color(0, 0, 0), "invalid", -1);
			inline static sur::Triggers::Rectangle* TRdefault = new sur::Triggers::Rectangle({ 0,0 }, { 0,0 }, "invalid", -1);
		};

		enum class Types {
			Rectangle, Line, Object, Triangle, Shape, Trigger_Rectangle
		};

		void Add(void* object, Types type);

		template<typename RetTy>
		RetTy* Get(std::string_view name = "", i32 index = -1);

		u32 GetCount(Types type);

		void State(Types type, bool active, std::string_view name = "", i32 index = -1);

		void Delete(Types type, std::string_view name = "", i32 index = -1);

		void ClearAll();
	}
	//
	//	Input
	// Classes.cpp
	struct Input {
		struct Mouse {
			Vec2f Position() const;
			bool LClick() const;
			bool RClick() const;
		};
		struct Keyboard {
			bool Key(Keys::Keys key) const;
			bool KeyDown(Keys::Keys key);
		private:
			Keys::Keys pressed[27] = { Keys::Keys::None };	// 27 because of the SPACE key
		};
		Mouse mouse;
		Keyboard keyboard;
	};
	//
	//	struct
	// Classes.cpp
	struct Map_Analyses {
		analyses::Array<i32> Collider, Trigger;
		analyses::Array<Color> Render;
		void operator ()(Maps map, Vec2 size);
		void operator ()(i32* cptr, i32* tptr, Color* rptr, Vec2 size);
	};

	struct CollisionPackage {
		Master* ptr; i16 steps;
	};

}