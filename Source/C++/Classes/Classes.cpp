

#include "Classes.h"



std::vector<i32> identitys;
std::vector<void*> ptrs;


extern sur::Map_Analyses _Amap;
extern std::vector<i32> trigger_identitys;
extern std::vector<void*> trigger_ptrs;

//
//	Master
//
void sur::Master::Move(Vec2f direction, bool detect)
{
	if(direction.x > 0)
		counterpos.x += direction.x;
	else
		counterneg.x += direction.x;
	if (direction.y > 0)
		counterpos.y += direction.y;
	else
		counterneg.y += direction.y;
	direction = { 0,0 };
	while (counterpos.x >= (f32)countercountpos.x) {
		direction.x += 1;
		countercountpos.x++;
	}
	while (counterpos.y >= (f32)countercountpos.y) {
		direction.y += 1;
		countercountpos.y++;
	}
	while (counterneg.x <= (f32)countercountneg.x) {
		direction.x -= 1;
		countercountneg.x--;
	}
	while (counterneg.y <= (f32)countercountneg.y) {
		direction.y -= 1;
		countercountneg.y--;
	}
	direction.y *= -1;
	if (detect) {
		i32 CurMove = 0;
		if (direction.y > 0) {	//Up
			for (i32 a = 1; a <= direction.y; a++) {
				for (i32 i = position.x; i < position.x + size.x; i++) {
					for (i32 j = 0; j < trigger_identitys.size(); j++) {
						if (_Amap.Trigger(i, position.y - a - 1) == trigger_identitys[j]) {
							MessageBoxA(NULL, "Trigger", "Trigger", MB_ICONERROR);
						}
					}
					for (i32 j = 0; j < identitys.size(); j++) {				
						if (_debug)
							_Amap.Render(i, position.y - a - 1, Color(0, 255, 0));
						if (_Amap.Collider(i, position.y - a - 1) == identitys[j] && this->id != identitys[j]) {
							if (callback != nullptr)
								callback((Master*)this, (Master*)ptrs[j]);
							if (static_cast<Master*>(ptrs[j])->callback != nullptr)
								static_cast<Master*>(ptrs[j])->callback((Master*)(ptrs[j]), this);
							goto dir1;
						}	
					}
				}
				CurMove = a;
			}
		dir1:
			MoveInject(1, CurMove);
		}
		if (direction.x > 0) {	//Right
			for (i32 a = 1; a <= direction.x; a++) {
				for (i32 i = position.y; i < position.y + size.y; i++) {
					for (i32 j = 0; j < trigger_identitys.size(); j++) {
						if (_Amap.Trigger(position.x + size.x + a - 1, i) == trigger_identitys[j]) {
							MessageBoxA(NULL, "Trigger", "Trigger", MB_ICONERROR);
						}
					}
					for (i32 j = 0; j < identitys.size(); j++) {
						if (_debug)
							_Amap.Render(position.x + size.x + a - 1, i, Color(0, 255, 0));
						if (_Amap.Collider(position.x + size.x + a - 1, i) == identitys[j] && this->id != identitys[j]) {
							if (callback != nullptr)
								callback((Master*)this, (Master*)ptrs[j]);
							if (static_cast<Master*>(ptrs[j])->callback != nullptr)
								static_cast<Master*>(ptrs[j])->callback((Master*)ptrs[j],this);
							goto dir2;
						}			
					}
				}
				CurMove = a;
			}
		dir2:
			MoveInject(2, CurMove);
		}
		if (direction.y < 0) {	//Down
			direction.y *= -1;
			for (i32 a = 0; a <= direction.y; a++) {
				for (i32 i = position.x; i < position.x + size.x; i++) {
					for (i32 j = 0; j < trigger_identitys.size(); j++) {
						if (_Amap.Trigger(i, position.y + size.y + a) == trigger_identitys[j]) {
							MessageBoxA(NULL, "Trigger", "Trigger", MB_ICONERROR);
						}
					}
					for (i32 j = 0; j < identitys.size(); j++) {			
						if (_debug)
							_Amap.Render(i, position.y + size.y + a, Color(0, 255, 0));
						if (_Amap.Collider(i, position.y + size.y + a) == identitys[j] && this->id != identitys[j]) {
							if (callback != nullptr)
								callback((Master*)this, (Master*)ptrs[j]);
							if (static_cast<Master*>(ptrs[j])->callback != nullptr)
								static_cast<Master*>(ptrs[j])->callback((Master*)ptrs[j], this);
							goto dir3;
						}
					}
				}
				CurMove = a;
			}
		dir3:
			MoveInject(3, CurMove);
		}
		if (direction.x < 0) {	//Left
			direction.x *= -1;
			for (i32 a = 1; a <= direction.x; a++) {
				for (i32 i = position.y; i < position.y + size.y; i++) {
					for (i32 j = 0; j < trigger_identitys.size(); j++) {
						if (_Amap.Trigger(position.x - a - 1, i) == trigger_identitys[j]) {
							MessageBoxA(NULL, "Trigger", "Trigger", MB_ICONERROR);
						}
					}
					for (i32 j = 0; j < identitys.size(); j++) {
						if (_debug)
							_Amap.Render(position.x - a - 1, i, Color(0, 255, 0));
						if (_Amap.Collider(position.x - a - 1, i) == identitys[j] && this->id != identitys[j]) {
							if (callback != nullptr)
								callback((Master*)this, (Master*)ptrs[j]);
							if (static_cast<Master*>(ptrs[j])->callback != nullptr)
								static_cast<Master*>(ptrs[j])->callback((Master*)ptrs[j],this);
							goto dir4;
						}
					}
				}
				CurMove = a;
			}
		dir4:
			MoveInject(4, CurMove);
		}
	}
	else {
		if (direction.y > 0)
			position.y -= (i32)direction.y;
		if (direction.x > 0)
			position.x += (i32)direction.x;
		if (direction.y < 0)
			position.y -= (i32)direction.y;
		if (direction.x < 0)
			position.x += (i32)direction.x;
	}
}

sur::Vec2 sur::Master::rot(Vec2 pos, Vec2 origin, i32 Angle)
{
	sur::Vec2 dist(pos - origin);
	return 	sur::Vec2((i32)(dist.x * cos(Angle * PI / 180) - dist.y * sin(Angle * PI / 180)),
		(i32)(dist.x * sin(Angle * PI / 180) + dist.y * cos(Angle * PI / 180))) + origin;
}

void sur::Master::MoveInject(i32 index, i32 CurMove)
{
	switch (index)
	{
	case 1:
		position.y -= CurMove;
		break;
	case 2:
		position.x += CurMove;
		break;
	case 3:
		position.y += CurMove;
		break;
	case 4:
		position.x -= CurMove;
		break;
	}
}
//
//	Render
//
void sur::Render::ClearScreenBuffer()
{
	std::fill(_map.RenderMap, _map.RenderMap + _window_size.x * _window_size.y, bg.ToCOLORREF());
	std::fill(_map.ColliderMap, _map.ColliderMap + _window_size.x * _window_size.y, 0);
	std::fill(_map.TriggerMap, _map.TriggerMap + _window_size.x * _window_size.y, 0);
}

void sur::Render::RenderScreenBuffer()
{
	BITMAPINFO bi = { 0 };
	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bi.bmiHeader.biWidth = _window_size.x;
	bi.bmiHeader.biHeight = _window_size.y;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 32;
	bi.bmiHeader.biCompression = BI_RGB;
	sleep_for(milliseconds(Wait));
	SetDIBitsToDevice(dc, 0, 0,_window_size.x, _window_size.y, 0, 0, 0, _window_size.x, _map.RenderMap, &bi, 0);
	frameCounter++;
}

void sur::Render::FPS()
{
	if (!thread) {
		thread = true;
		std::thread t(&sur::Render::FPS, this);
		t.detach();
		return;
	}
	std::string Buffer;
	char* title = new char[100];
	GetWindowTextA(_hwnd, title, 100);
	while (true) {		
		sleep_for(seconds(1));
		Buffer += title;
		Buffer += " FPS: ";
		Buffer += std::to_string(frameCounter);
		SetWindowTextA(_hwnd, Buffer.c_str());
		Buffer = "";
		frameCounter = 0;
	}
}

void sur::Render::DebugConsole(bool Show)
{
	if (!Show)
		ShowWindow(GetConsoleWindow(), SW_HIDE);
}
//
//	Camera
//
void sur::Camera::Move(Vec2f direction)
{
	using namespace sur::Instancer;
	direction.invert();
	for (i32 i = 0; i < restricted::rectangles->size(); i++) {
		restricted::rectangles->at(i)->Move(direction, false);
	}
	for (i32 i = 0; i < restricted::lines->size(); i++) {
		restricted::lines->at(i)->Move(direction, false);
	}
	for (i32 i = 0; i < restricted::objects->size(); i++) {
		restricted::objects->at(i)->Move(direction, false);
	}
	for (i32 i = 0; i < restricted::triangles->size(); i++) {
		restricted::triangles->at(i)->Move(direction, false);
	}
	for (i32 i = 0; i < restricted::shapes->size(); i++) {
		restricted::shapes->at(i)->Move(direction, false);
	}
	for (i32 i = 0; i < restricted::trigger_rectangles->size(); i++) {
		restricted::trigger_rectangles->at(i)->Move(direction);
	}
}
//
//	Rectangle
//
sur::Rectangle::Rectangle(Vec2 position, Vec2 size, Color color, const std::string& name, i32 id, cb_ptr<Master*> callback)
	:color(color), Master(name,id, position, size, callback)
{
	type = Type::Rectangle;
	identitys.push_back(id);
	ptrs.push_back(this);
}

void sur::Rectangle::Bind(bool Render,bool Collider)
{
	for (i32 i = position.y; i < position.y + size.y; i++)
		for (i32 j = position.x; j < position.x + size.x; j++) {
			if (Render)
				_Amap.Render(j, i, color.ToCOLORREF());
			if (Collider)
				_Amap.Collider(j - CO, i - CO, id);
		}
}
//
//	Line
//
sur::Line::Line(Vec2 start, Vec2 end, Color color, const std::string& name, i32 id, cb_ptr<Master*> callback)
	: start(start), end(end), color(color), Master(name, id, callback)
{
	type = Type::Line;
	identitys.push_back(id);
	ptrs.push_back(this);
}

void sur::Line::Bind(bool Render, bool Collider)
{
	Vec2 end = this->end;
	Vec2 start = this-> start;
	if (start.x == end.x) start.x--;
	if (this->start.y > this->end.y && this->start.x > this->end.x) {
		std::swap(start.y, end.y);
		std::swap(start.x, end.x);
	}
	i32 Dx, Dy;
	f32 RunsThrough;
	Dx = end.x - start.x;
	Dy = end.y - start.y;
	RunsThrough = (f32)Dy / (f32)Dx;
	if (RunsThrough >= 0) {
		i32 tempy = start.y;
		f32 counter = 0.0f;
		i32 countcounter = 1;
		for (i32 i = start.x; i <= end.x; i++) {
			if(Render)
				_Amap.Render(i, tempy, color.ToCOLORREF());
			if(Collider)
				_Amap.Collider(i - CO, tempy - CO, id);	
			while (counter >= countcounter) {
				tempy++;
				if (Render)
					_Amap.Render(i, tempy, color.ToCOLORREF());
				if (Collider)
					_Amap.Collider(i - CO, tempy - CO, id);
				countcounter++;
			}
			counter += RunsThrough;
		}
	}
	else {
		RunsThrough *= -1;
		i32 tempy = start.y;
		f32 counter = 0.0f;
		i32 countcounter = 1;
		bool runned = false;
		for (i32 i = start.x; i <= end.x; i++) {
			if (Render)
				_Amap.Render(i, tempy, color.ToCOLORREF());
			if (Collider)
				_Amap.Collider(i - CO, tempy - CO, id);
			while (counter >= countcounter) {
				tempy--;
				if (Render)
					_Amap.Render(i, tempy, color.ToCOLORREF());
				if (Collider)
					_Amap.Collider(i - CO, tempy - CO, id);
				countcounter++;
			}
			runned = true;	
			counter += RunsThrough;
		}
		if (!runned) {
			RunsThrough = (f32)Dx / (f32)Dy;
			RunsThrough *= -1;
			i32 tempx = start.x;
			for (i32 i = start.y; i <= end.y; i++) {
				if (Render)
					_Amap.Render(tempx, i, color.ToCOLORREF());
				if(Collider)
					_Amap.Collider(tempx - CO, i - CO, id);
				while (counter >= countcounter) {
					tempx--;
					if (Render)
						_Amap.Render(tempx, i, color.ToCOLORREF());
					if (Collider)
						_Amap.Collider(tempx - CO, i - CO, id);
					countcounter++;
				}
				counter += RunsThrough;
			}
		}
	}
}
//
//	Custom wire shape
//
sur::Shape::Shape(Color color, const std::string& name, i32 id, cb_ptr<Master*> callback) : color(color)
{
	this->name = name;
	type = Type::Shape;
	identitys.push_back(id);
	ptrs.push_back(this);
	this->id = id;
}

void sur::Shape::Gen()
{
	for (i32 i = 0; i < vec->size() - 1; ++i) {
		lines->push_back(new Line(vec->at(i), vec->at(i + 1), color, "ShapeLine" + std::to_string(i), id));
	}
}

void sur::Shape::Bind(bool Render, bool Collider)
{
	for (auto&& it : *lines)
		it->Bind(Render,Collider);
}
//
//	Input
//

//	Mouse
sur::Vec2 sur::Input::Mouse::Position() const
{
	POINT point;
	GetCursorPos(&point);
	ScreenToClient(_hwnd, &point);
	if (point.x < 0 || point.y < 0)
		return { 0,0 };
	if (point.x > _window_size.x - 1 || point.y > _window_size.y - 1)
		return { _window_size.x - 1, _window_size.y - 1};
	return{ point.x, point.y };
}

bool sur::Input::Mouse::LClick() const
{
	if (GetAsyncKeyState(VK_LBUTTON))
		return true;
	return false;
}

bool sur::Input::Mouse::RClick() const
{
	if (GetAsyncKeyState(VK_RBUTTON))
		return true;
	return false;
}

// Keyboard
bool sur::Input::Keyboard::Key(Keys::Keys key) const
{
	if (GetAsyncKeyState(key))
		return true;
	return false;
}
//
//	Map_Analyses
//
void sur::Map_Analyses::operator()(Maps map, Vec2 size)
{
	Collider(map.ColliderMap, size);
	Trigger(map.ColliderMap, size);
	Render(map.RenderMap, size);
}

void sur::Map_Analyses::operator()(i32* cptr, i32* tptr, DWORD* rptr, sur::Vec2 size)
{
	Collider(cptr, size);
	Trigger(tptr, size);
	Render(rptr, size);
}

