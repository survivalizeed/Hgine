

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
		std::string name;
			
		Master(const std::string& name) : name(name) {}

		inline void SetName(const std::string& name) { this->name = name; }

	public:
		int id;
		cb_ptr<Master*> callback = nullptr;

		inline const std::string& GetName() const { return name; }


		void GenId();
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
		Color bg;
		HDC dc;
	public:

		Render(Color bg, int Wait = 0) : bg(bg), Wait(Wait) { dc = GetDC(_hwnd);}

		void ClearScreenBuffer();

		void RenderScreenBuffer();

		void FPS();

	};			
	//
	//	Shape: Rectangle
	//
	class Rectangle : public Master {
	private:	
		sur::Vec2 position;
		sur::Vec2 size;
		Color color;
	public:
		Rectangle() = default;

		Rectangle(sur::Vec2 position, sur::Vec2 size, Color color, std::string name)
			: position(position), size(size), color(color), Master(name) {}
		
		inline void operator()(sur::Vec2 position, sur::Vec2 size, Color color, std::string name) 
		{ this->position = position; this->size = size; this->color = color; this->name = name; }

		void Bind(bool Collider);

		void Move(sur::Vec2 direction);
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

		Line(sur::Vec2 start, sur::Vec2 end, Color color, std::string name)
			: start(start), end(end), color(color), Master(name) {}
		
		inline void operator()(sur::Vec2 start, sur::Vec2 end, Color color) 
		{ this->start = start; this->end = end; this->color = color; SetName(name); }

		inline void End(sur::Vec2 end) { this->end = end; }

		inline void Start(sur::Vec2 start) { this->start = start; }

		inline void SetColor(Color color) { this->color = color; }

		void Bind();
	};
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