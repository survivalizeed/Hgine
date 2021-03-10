

#pragma once

#include "includes.h"

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
			: name(name), id(id) {}		//Line

		Master(const std::string& name, int id, sur::Vec2 position)
			: name(name), id(id), position(position) {}		//OBJ

		Master(const std::string& name, int id, sur::Vec2 position, sur::Vec2 size)
			: name(name), id(id), position(position), size(size) {}		//Rectangle

		virtual void MoveInject(int index, int curmove) {}

	public:
		int id;
		cb_ptr<Master*> callback = nullptr;	

		inline const std::string& GetName() const { return name; }

		inline sur::Vec2 GetPosition() const { return position; }

		inline sur::Vec2 GetSize() const { return size; }
		
		inline void SetPos(sur::Vec2 position) { this->position = position; }

		void Move(sur::Vec2 direction);

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
	//	Shape: Rectangle
	//
	class Rectangle : public Master {
	private:	
		Color color;
		void MoveInject(int index, int curmove) override;
	public:
		Rectangle() = default;

		Rectangle(sur::Vec2 position, sur::Vec2 size, Color color, std::string name,int id);
		
		inline void operator()(sur::Vec2 position, sur::Vec2 size, Color color, std::string name, int id)
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
		LoadObj() = default;

		LoadObj(const char* Path, sur::Vec2 position, std::string name, int id);

		inline void operator()(const char* Path, sur::Vec2 position, std::string name, int id)
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

		Line() = default;

		Line(sur::Vec2 start, sur::Vec2 end, Color color, std::string name, int id);
		
		inline void operator()(sur::Vec2 start, sur::Vec2 end, Color color, std::string name, int id)
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
	// Instancer <- For object management
	//
	namespace Instancer {
		namespace restricted {
			static std::vector<Rectangle*>* rectangles = new std::vector<Rectangle*>;
			static std::vector<Line*>* lines = new std::vector<Line*>;
			static std::vector<LoadObj*>* objects = new std::vector<LoadObj*>;

			// To return if nothing was found -> prevent error of nullpointer
			static Rectangle* Rdefault = new Rectangle({ 0,0 }, { 0,0 }, Color(0, 0, 0), "invalid", 0);
			static Line* Ldefault = new Line({ 0,0 }, { 0,0 }, Color(0, 0, 0), "invalid", 0);
			static LoadObj* Odefault = new LoadObj("invalid", { 0,0 }, "invalid", 0);
		}
		enum class Types {
			Rectangle, Line, Obj
		};

		void Add(void* object, Types type);

		sur::Rectangle* GetRect(const std::string& name = "", int index = -1);

		sur::Line* GetLine(const std::string& name = "", int index = -1);

		sur::LoadObj* GetObj(const std::string& name = "", int index = -1);

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