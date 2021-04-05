

#pragma once

#include "../Functional/includes.h"

extern HWND _hwnd;


namespace sur {
	//
	//	Static var
	//

	//
	//	Static func
	//

	//
	//	Classes
	//
	//
	//	Master: Defines the standard attributes of an object
	//
	class Master {
	protected:

		sur::Vec2f counter;
		sur::Vec2 countercountpos = { 1,1 };
		sur::Vec2 countercountneg = { -1,-1 };

		sur::Vec2 moveiter;
		std::string name;
		sur::Vec2 position;
		sur::Vec2 size;

		Master(const std::string& name, i32 id, cb_ptr<Master*> callback = nullptr)
			: name(name), id(id), callback(callback) {}		//Line, Triangle

		Master(const std::string& name, i32 id, sur::Vec2 position, cb_ptr<Master*> callback = nullptr)
			: name(name), id(id), position(position), callback(callback) {}		//OBJ

		Master(const std::string& name, i32 id, sur::Vec2 position, sur::Vec2 size, cb_ptr<Master*> callback = nullptr)
			: name(name), id(id), position(position), size(size), callback(callback) {}		//Rectangle

		sur::Vec2 rot(sur::Vec2 pos, sur::Vec2 origin, i32 Angle);
		
		virtual void MoveInject(i32 index, i32 CurMove);

	public:
		enum class Type {
			Rectangle, Object, Triangle, Line, Trigger
		} type;

		//Don't use this variable
		bool active = true;

		i32 id;

		cb_ptr<Master*> callback = nullptr;

		Master() = default;

		virtual inline const std::string& GetName() const { return name; }

		virtual inline sur::Vec2 GetPosition() const { return position; }

		virtual inline sur::Vec2 GetSize() const { return size; }

		virtual inline void SetPosition(sur::Vec2 position) { this->position = position; }

		inline sur::Vec2 GetOrigin() const { return GetPosition() + GetSize() / 2; }

		inline bool State() const { return active; }

		void Move(sur::Vec2f direction, bool detect);
	};
	//
	//	Render class
	//
	class Render {
	private:
		bool thread = false;
		i32 frameCounter = 0;
		i32 Wait;
		HDC dc;
		Color bg;
	public:

		Render(Color bg, i32 Wait = 0) : bg(bg), Wait(Wait) { dc = GetDC(_hwnd); }

		void ClearScreenBuffer();

		void RenderScreenBuffer();

		void FPS();

		void DebugConsole(bool Show);
	};
	//
	// Camera class
	//
	namespace Camera {
		void Move(sur::Vec2f direction);
	};
	//
	//	Shape: Rectangle
	//
	class Rectangle : public Master {
	private:
		Color color;
	public:

		Rectangle(sur::Vec2 position, sur::Vec2 size, Color color, const std::string& name, i32 id, cb_ptr<Master*> callback = nullptr);

		void Bind(bool Render, bool Collider);

	};
	//
	//	Load objects that were created with the Hgineres editor
	//
	class Object : public Master {
	protected:
		i32 x = 0;
		i32 y = 0;
		i32 previous_angle;
		std::string path;
		bool rotatecpy = false;

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

		Object(const std::string& path, sur::Vec2 position, const std::string& name, i32 id, cb_ptr<Master*> callback = nullptr);

		// Don't delete those objects, just unactivate them
		Object(const Object* const obj, sur::Vec2 position, const std::string& name, i32 id, cb_ptr<Master*> callback = nullptr);

		void Bind(bool Render, bool Collider, ColliderType collidertype);

		void Rotate(sur::Vec2 origin, i32 Angle);

		~Object() {
			delete YCoords, XCoords, Colors;
		}
	};
	//
	//	Shape: Procedual Line
	//
	class Line : public Master {
	private:
		sur::Vec2 start;
		sur::Vec2 end;
		Color color;
		size_t lenght = 0;
	public:

		Line(sur::Vec2 start, sur::Vec2 end, Color color, const std::string& name, i32 id, cb_ptr<Master*> callback = nullptr);

		inline void End(sur::Vec2 end) { this->end = end; }

		inline void Start(sur::Vec2 start) { this->start = start; }

		inline void SetColor(Color color) { this->color = color; }

		void Bind(bool Render, bool Collider);

		//Destructor
	};
	//
	//	Shape: Triangle
	//
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

	public:

		Triangle(sur::Vec2 p1, sur::Vec2 p2, sur::Vec2 p3, Color color, const std::string& name, i32 id, cb_ptr<Master*> callback = nullptr);

		inline void SetPosition(i32 which, sur::Vec2 pos) {
			switch (which) {
			case 1: p1 = pos; return;
			case 2: p2 = pos; return;
			case 3: p3 = pos; return;
			}
		}
		void Bind(bool Render, bool Collider);
	};
	//
	//	Shape: Custom wire shape
	//
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
		Shape(Color color, i32 id, cb_ptr<Master*> callback = nullptr)
			: color(color)
		{
			this->id = id;
		}

		template<VEC F, VEC ... R>
		void Pass(F f, R ... r) {
			vec->push_back((sur::Vec2)f);
			Pass(r...);
		}
		
		void Bind(bool Render, bool Collider);
	};
	//
	//	Instancer <- For object management
	//
	namespace Instancer {
		namespace restricted {
			static std::vector<Rectangle*>* rectangles = new std::vector<Rectangle*>;
			static std::vector<Line*>* lines = new std::vector<Line*>;
			static std::vector<Object*>* objects = new std::vector<Object*>;
			static std::vector<Triangle*>* triangles = new std::vector<Triangle*>;

			// To return if nothing was found -> prevent error of nullpointer
			static Rectangle* Rdefault = new Rectangle({ 0,0 }, { 0,0 }, Color(0, 0, 0), "invalid", -1);
			static Line* Ldefault = new Line({ 0,0 }, { 0,0 }, Color(0, 0, 0), "invalid", -1);
			static Object* Odefault = new Object("invalid", { 0,0 }, "invalid", -1);
			static Triangle* Tdefault = new Triangle({ 0,0 }, { 0,0 }, { 0,0 }, Color(0, 0, 0), "invalid", -1);
		}

		enum class Types {
			Rectangle, Line, Object, Triangle
		};

		void Add(void* object, Types type);

		sur::Rectangle* GetRect(const std::string& name = "", i32 index = -1);

		sur::Line* GetLine(const std::string& name = "", i32 index = -1);

		sur::Object* GetObj(const std::string& name = "", i32 index = -1);

		sur::Triangle* GetTri(const std::string& name = "", i32 index = -1);

		i32 GetCount(Types type);

		void State(Types type, bool active, const std::string& name = "", i32 index = -1);

		void Delete(Types type, const std::string& name = "", i32 index = -1);
	}
	//
	//	Triggers
	//
	namespace Triggers {
		class Rectangle : public Master
		{
		private:

		public:
			Rectangle(sur::Vec2 position, sur::Vec2 size, const std::string& name, i32 id, cb_ptr<Master*> callback = nullptr);

			inline void Move(sur::Vec2f direction) cpar(Master::Move(direction, false))

			void Bind();
		};
	}
	//
	//	Input
	//
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
	//
	struct Map_Analyses {
		analyses::Array<i32> Collider, Trigger;
		analyses::Array<DWORD> Render;
		void operator ()(sur::Maps map, sur::Vec2 size);		
		void operator ()(i32* cptr, i32* tptr, DWORD* rptr, sur::Vec2 size);
	};

}