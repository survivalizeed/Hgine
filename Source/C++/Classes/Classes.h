

#pragma once

#include "../Functional/includes.h"

extern HWND _hwnd;


namespace sur {
	//
	//	Classes
	//
	struct CollisionPackage;
	//
	//	Master: Defines the standard attributes of an object
	// Classes.cpp
	class Master {
	protected:

		Vec2f counterneg = { -0.f,-0.f };
		Vec2f counterpos = { 0.f,0.f };	
		Vec2 countercountpos = { 1,1 };
		Vec2 countercountneg = { -1,-1 };

		Vec2 moveiter;
		std::string name;
		Vec2 position;
		Vec2 size;

		std::vector<CollisionPackage>* packs = new std::vector<CollisionPackage>;	// Will be used by all objects -> ok, because it will get cleared each time
		
		Master(const std::string& name, i32 id, cb_ptr<Master*> callback = nullptr)
			: name(name), id(id), callback(callback) {}		//Line, Triangle

		Master(const std::string& name, i32 id, Vec2 position, cb_ptr<Master*> callback = nullptr)
			: name(name), id(id), position(position), callback(callback) {}		//OBJ

		Master(const std::string& name, i32 id, Vec2 position, Vec2 size, cb_ptr<Master*> callback = nullptr)
			: name(name), id(id), position(position), size(size), callback(callback) {}		//Rectangle

		Vec2 rot(Vec2 pos, Vec2 origin, i32 Angle);
		
		virtual void MoveInject(i32 index, i32 CurMove);

		Vec2 MovQueue(Vec2f direction);

	public:
		enum class Type {
			Rectangle, Object, Triangle, Line, Shape, Trigger_Rectangle
		} type;

		std::vector<i32> ignore;

		//Don't use this variable
		bool active = true;

		i32 id;

		cb_ptr<Master*> callback = nullptr;

		Master() = default;

		inline const std::string& GetName() const { return name; }

		virtual inline sur::Vec2 GetPosition() const { return position; }

		virtual inline sur::Vec2 GetSize() const { return size; }

		virtual inline void SetPosition(sur::Vec2 position) { this->position = position; }

		inline sur::Vec2 GetOrigin() const { return GetPosition() + GetSize() / 2; }

		inline bool State() const { return active; }

		virtual void Move(sur::Vec2f direction, bool detect);
	};
	//
	//	Render class
	// Classes.cpp
	class Render {
	private:
		bool thread = false;
		i32 frameCounter = 0;
		i32 Wait;
		HDC dc;
		Color bg;
		bool dontFillBackground;
	public:

		Render(Color bg, bool dontFillBackground, i32 Wait = 0) : bg(bg), dontFillBackground(dontFillBackground), Wait(Wait)
		{ dc = GetDC(_hwnd); }

		void ClearScreenBuffer();

		void RenderScreenBuffer();

		void FPS();

		void DebugConsole(bool Show);
	};
	//
	// Camera class
	// Classes.cpp
	namespace Camera {
		void Move(sur::Vec2f direction);
	};
	//
	//	Shape: Rectangle
	// Classes.cpp
	class Rectangle : public Master {
	private:
		Color color;
	public:

		Rectangle(sur::Vec2 position, sur::Vec2 size, Color color, const std::string& name, i32 id,
			const std::vector<int>& ignoreids = {0}, cb_ptr<Master*> callback = nullptr);

		void Bind(bool Render, bool Collider);
	};
	//
	//	Load objects that were created with the Hgineres editor
	// LoadObj.cpp
	class Object : public Master {
	protected:
		i32 x = 0;
		i32 y = 0;
		i32 previous_angle;
		bool rotatecpy = false;
		std::string path;		
		sRGB tint_by;

		std::vector<i32>* XCoordsO = new std::vector<i32>;
		std::vector<i32>* YCoordsO = new std::vector<i32>;
		std::vector<Color>* ColorsO = new std::vector<Color>;
		
		std::vector<i32>* XCoordsC = nullptr;
		std::vector<i32>* YCoordsC = nullptr;
		std::vector<Color>* ColorsC = nullptr;

		std::vector<i32>* XCoords = XCoordsO;
		std::vector<i32>* YCoords = YCoordsO;
		std::vector<Color>* Colors = ColorsO;
		
		std::vector<i32>* MaxX = new std::vector<i32>;

		void Load();

	public:

		bool parentmem;

		Object(const std::string& path, sur::Vec2 position, const std::string& name, i32 id, const std::vector<int>& ignoreids = {0},
			cb_ptr<Master*> callback = nullptr);

		Object(const Object* const obj, sur::Vec2 position, const std::string& name, i32 id, const std::vector<int>& ignoreids = {0},
			cb_ptr<Master*> callback = nullptr);

		void Bind(bool Render, ColliderType collidertype);

		void Rotate(sur::Vec2 origin, i32 Angle);

		void LSD();

		inline void Tint(sRGB rgb_intensity) { tint_by = rgb_intensity; }

		~Object() {
			delete YCoordsO, XCoordsO, ColorsO;
			if (rotatecpy)
				delete YCoordsC, XCoordsC, ColorsC;
		}
	};
	//
	//	Shape: Procedual Line
	// Classes.cpp
	class Line : public Master {
	private:
		sur::Vec2 start;
		sur::Vec2 end;
		Color color;
		size_t lenght = 0;
	public:

		Line(sur::Vec2 start, sur::Vec2 end, Color color, const std::string& name, i32 id, const std::vector<int>& ignoreids = {0},
			cb_ptr<Master*> callback = nullptr);

		inline void End(sur::Vec2 end) { this->end = end; }

		inline void Start(sur::Vec2 start) { this->start = start; }

		inline void SetColor(Color color) { this->color = color; }

		void Bind(bool Render, bool Collider);
	};
	//
	//	Shape: Triangle
	// Triangle.cpp
	class Triangle : public Master {
	private:
		sur::Vec2 p1, p2, p3;
		Color color;

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

		void Line(sur::Vec2 start, sur::Vec2 end, std::vector<sur::Vec2>* line,bool Render, bool Collider);

		void Fill(LineVector& linevector);

		void MoveInject(i32 index, i32 CurMove) override;

	public:

		Triangle(sur::Vec2 p1, sur::Vec2 p2, sur::Vec2 p3, Color color, const std::string& name, i32 id, 
			const std::vector<int>& ignoreids = {0}, cb_ptr<Master*> callback = nullptr);

		inline void SetPosition(i32 which, sur::Vec2 pos) {
			switch (which) {
			case 1: p1 = pos; return;
			case 2: p2 = pos; return;
			case 3: p3 = pos; return;}
		}

		void Bind(bool Render, bool Collider);
	};
	//
	//	Shape: Custom wire shape
	// Classes.cpp
	class Shape : public Master {
	private:
		Color color;
		std::vector<sur::Vec2>* vec = new std::vector<sur::Vec2>;
		std::vector<sur::Line*>* lines = new std::vector<sur::Line*>;
		
		void Gen();

		template<VEC R>
		void Pass(R r){
			vec->push_back((sur::Vec2)r);
			Gen();
		}

	public:
		Shape(Color color, const std::string& name, i32 id, const std::vector<int>& ignoreids = {0},
			cb_ptr<Master*> callback = nullptr);

		// Call after constructor
		template<VEC F, VEC ... R>
		void Pass(F f, R ... r) {
			vec->push_back((sur::Vec2)f);
			Pass(r...);
		}
		
		void Bind(bool Render, bool Collider);
	};
	//
	//	Triggers
	// Classes_2.cpp
	namespace Triggers {
		class Rectangle : public Master
		{
		private:

		public:
			Rectangle(sur::Vec2 position, sur::Vec2 size, const std::string& name, i32 id, const std::vector<int>& ignoreids = {0},
				cb_ptr<Master*> callback = nullptr);

			inline void Move(sur::Vec2f direction) cpar(Master::Move(direction, false))

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
		RetTy* Get(const std::string& name = "", i32 index = -1);

		u32 GetCount(Types type);

		void State(Types type, bool active, const std::string& name = "", i32 index = -1);

		void Delete(Types type, const std::string& name = "", i32 index = -1);
	}

	//
	//	Input
	// Classes.cpp
	struct Input {
		struct Mouse {
			sur::Vec2 Position() const;
			bool LClick() const;
			bool RClick() const;
		};
		struct Keyboard {
			bool Key(Keys::Keys key) const;
		};
		Mouse mouse;
		Keyboard keyboard;
	};
	//
	//	struct
	// Classes.cpp
	struct Map_Analyses {
		analyses::Array<i32> Collider, Trigger;
		analyses::Array<DWORD> Render;
		void operator ()(sur::Maps map, sur::Vec2 size);		
		void operator ()(i32* cptr, i32* tptr, DWORD* rptr, sur::Vec2 size);
	};
	
	struct CollisionPackage {
		Master* ptr; i16 steps;
	};

}