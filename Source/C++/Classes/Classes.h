

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
		sur::Vec2 moveiter;
		std::string name;
		sur::Vec2 position;
		sur::Vec2 size;

		Master(const std::string& name, int id)	
			: name(name), id(id) {}		//Line, Triangle

		Master(const std::string& name, int id, sur::Vec2 position)
			: name(name), id(id), position(position) {}		//OBJ

		Master(const std::string& name, int id, sur::Vec2 position, sur::Vec2 size)
			: name(name), id(id), position(position), size(size) {}		//Rectangle

		virtual void MoveInject(int index, int curmove) {}

	public:
		int id;
		cb_ptr<Master*> callback = nullptr;	

		virtual inline const std::string& GetName() const { return name; }

		virtual inline sur::Vec2 GetPosition() const { return position; }

		virtual inline sur::Vec2 GetSize() const { return size; }
		
		virtual inline void SetPosition(sur::Vec2 position) { this->position = position; }

		void Move(sur::Vec2 direction, bool detect);

	};
	//
	//	Render class
	//
	class Render
	{
	private:
		bool thread = false;
		int frameCounter = 0;
		int Wait;
		HDC dc;
		Color bg;
	public:

		Render(Color bg, int Wait = 0) : bg(bg), Wait(Wait) { dc = GetDC(_hwnd);}

		void ClearScreenBuffer();

		void RenderScreenBuffer();

		void FPS();

		void DebugConsole(bool Show);
	};
	//
	// Camera class
	//
	namespace Camera {
		void Move(sur::Vec2 direction);
	};
	//
	//	Shape: Rectangle
	//
	class Rectangle : public Master {
	private:	
		Color color;
		void MoveInject(int index, int curmove) override;
	public:
		Rectangle() = delete;

		Rectangle(sur::Vec2 position, sur::Vec2 size, Color color, const std::string& name,int id);
		
		inline void operator()(sur::Vec2 position, sur::Vec2 size, Color color, const std::string& name, int id)
		{
			this->position = position; this->size = size; this->color = color; this->name = name; this->id = id;
		}

		void Bind(bool Collider);

		//Destructor
	};
	//
	//	Load objects that were created with the Hgineres editor
	//
	class LoadObj : public Master
	{
	private:
		int x = 0;
		int y = 0;
		const char* Path;

		std::vector<int>* YCoords = new std::vector<int>;
		std::vector<int>* XCoords = new std::vector<int>;
		std::vector<Gdiplus::Color>* Colors = new std::vector<Gdiplus::Color>;
		std::vector<int>* MaxX = new std::vector<int>;

		void Load();

		void MoveInject(int index, int curmove) override;

	public:
		LoadObj() = delete;

		LoadObj(const char* Path, sur::Vec2 position, const std::string& name, int id);

		inline void operator()(const char* Path, sur::Vec2 position, const std::string& name, int id)
		{
			this->Path = Path; this->position = position; this->name = name; this->id = id; Load();
		}

		void Bind(bool Collider, ColliderType collidertype);

		~LoadObj() {
			delete YCoords, XCoords, Colors;
		}
	};
	//
	//	Shape: Procedual Line
	//
	class Line : public Master{
	private:
		sur::Vec2 start;
		sur::Vec2 end;
		Color color;
		size_t lenght = 0;
	public:

		Line() = delete;

		Line(sur::Vec2 start, sur::Vec2 end, Color color, const std::string& name, int id);
		
		inline void operator()(sur::Vec2 start, sur::Vec2 end, Color color, const std::string& name, int id)
		{
			this->start = start; this->end = end; this->color = color; this->name = name; this->id = id;
		}

		inline void End(sur::Vec2 end) { this->end = end; }

		inline void Start(sur::Vec2 start) { this->start = start; }

		inline void SetColor(Color color) { this->color = color; }

		void Bind(bool Collider);

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
			
			std::vector<Vec2>* get(int i);
			
			std::vector<Vec2>* getother();
		} linevector;

		void Line(sur::Vec2 start, sur::Vec2 end, std::vector<sur::Vec2>* line, bool Collider);

		void Fill(LineVector& linevector);

	public:
		Triangle() = delete;

		Triangle(sur::Vec2 p1, sur::Vec2 p2, sur::Vec2 p3, Color color, const std::string& name, int id);

		inline void operator ()(sur::Vec2 p1, sur::Vec2 p2, sur::Vec2 p3, Color color, const std::string& name, int id)
		{
			this->p1 = p1; this->p2 = p2; this->p3 = p3; this->color = color; this->name = name; this->id = id;
		}

		inline void SetPosition(int which, sur::Vec2 pos){
			switch (which) {
			case 1: p1 = pos; return;
			case 2: p2 = pos; return;
			case 3: p3 = pos; return;
			}
		}

		void Bind(bool Collider);
	};
	//
	// Instancer <- For object management
	//
	namespace Instancer {
		namespace restricted {
			static std::vector<Rectangle*>* rectangles = new std::vector<Rectangle*>;
			static std::vector<Line*>* lines = new std::vector<Line*>;
			static std::vector<LoadObj*>* objects = new std::vector<LoadObj*>;

			// To return if nothing was found -> prevent error of nullpointer
			static Rectangle* Rdefault = new Rectangle({ 0,0 }, { 0,0 }, Color(0, 0, 0), "invalid", -1);
			static Line* Ldefault = new Line({ 0,0 }, { 0,0 }, Color(0, 0, 0), "invalid", -1);
			static LoadObj* Odefault = new LoadObj("invalid", { 0,0 }, "invalid", -1);
		}
		enum class Types {
			Rectangle, Line, Obj
		};

		void Add(void* object, Types type);

		sur::Rectangle* GetRect(const std::string& name = "", int index = -1);

		sur::Line* GetLine(const std::string& name = "", int index = -1);

		sur::LoadObj* GetObj(const std::string& name = "", int index = -1);

		int GetCount(Types type);

		void Delete(Types type, const std::string& name = "", int index = -1);
	}
	//
	// Input
	//
	struct Input {
		struct Mouse {
			sur::Vec2 Position() const;
			bool LClick() const;
			bool RClick() const;
		};
		struct Keyboard {
			bool Key(Keys key) const;
		};
		Mouse mouse;
		Keyboard keyboard;
	};
	//
	// struct
	//
	struct Map_Analyses {
		analyses::Array<int> Collider, Trigger;
		analyses::Array<DWORD> Render;
		void operator ()(sur::Maps map, sur::Vec2 size);		
		void operator ()(int* cptr, int* tptr, DWORD* rptr, sur::Vec2 size);
	};

}