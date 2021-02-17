

#pragma once

#include "includes.h"

extern HWND _hwnd;


namespace sur {
	//
	//static
	//
	static std::vector<int> identitys;
	//
	// class
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
	class Rectangle {
	private:
		size_t idindex;
		sur::Vec2 position;
		sur::Vec2 size;
		std::string name;
		Color color;
	public:
		int id;
		Rectangle(sur::Vec2 position, sur::Vec2 size, Color color, std::string name)
			: position(position), size(size), color(color), name(name){}
		
		inline void operator()(sur::Vec2 position, sur::Vec2 size, Color color, std::string name) {
			this->position = position;
			this->size = size;
			this->color = color;
			this->name = name;
		}
		
		void Id();

		void Bind(bool Collider);

		void Move(sur::Vec2 direction);

		
	};
	//
	//	Shape: Procedual Line
	//
	class Line{
	private:
		size_t idindex;
		sur::Vec2 start;
		sur::Vec2 end;
		Color color;
		size_t lenght = 0;
		HDC dc;
	public:
		int id;
		Line(sur::Vec2 start, sur::Vec2 end, Color color)
			: start(start), end(end), color(color) { dc = GetDC(_hwnd); }
		
		inline void operator()(sur::Vec2 start, sur::Vec2 end, Color color) {
			this->start = start;
			this->end = end;
			this->color = color;
		}

		inline void End(sur::Vec2 end){ 
			this->end = end;
		}

		inline void Start(sur::Vec2 start) {
			this->start = start;
		}

		inline void SetColor(Color color) {
			this->color = color;
		}

		void Bind();
	};
	//
	// Input
	//
	struct Input {
		struct Mouse {
			sur::Vec2 Position();
			bool LClick();
			bool RClick();
		};
		struct Keyboard {
			bool Key(Keys key);
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