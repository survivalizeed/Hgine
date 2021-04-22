

#include "Classes.h"


std::vector<i32> identitys;
std::vector<void*> ptrs;


extern sur::Map_Analyses _Amap;
extern std::vector<i32> trigger_identitys;
extern std::vector<void*> trigger_ptrs;

sur::CollisionPackage CheckCollision(sur::Master* object, const sur::Vec2& pos, i32 dir, const Axis& axis)
{
	using sur::Master;
	i16 i = 1;
	bool neg = false;
	if (dir < 0)
		neg = true;

	switch (axis)
	{
	case Axis::X:
		if (!neg) {
			for (; i <= dir; ++i)
				for (i32 j = 0; j < identitys.size(); ++j)
						if (_debug)
							_Amap.Render(pos.x + i, pos.y, Color(255, 0, 0));
						else if (_Amap.Collider(pos.x + i, pos.y) == identitys[j] && object->id != identitys[j]) {
							for (i32 k = 0; k < object->ignore.size(); ++k) {
								if (object->ignore[k] == identitys[j])
									return { nullptr, (i16)dir };
							}
							return { (Master*)ptrs[j], --i };
						}
			return { nullptr, (i16)dir };
		}
		dir *= -1;
		for (; i <= dir; ++i)
			for (i32 j = 0; j < identitys.size(); ++j)		
					if (_debug)
						_Amap.Render(pos.x - i, pos.y, Color(255, 0, 0));
					else if (_Amap.Collider(pos.x - i, pos.y) == identitys[j] && object->id != identitys[j]) {
						for (i32 k = 0; k < object->ignore.size(); ++k) {
							if (object->ignore[k] == identitys[j])
								return { nullptr, (i16)dir };
						}
						return { (Master*)ptrs[j], --i };
					}
		return { nullptr, (i16)dir };

	case Axis::Y:
		if (!neg) {
			for (; i <= dir; ++i)
				for (i32 j = 0; j < identitys.size(); ++j)
						if (_debug)
							_Amap.Render(pos.x, pos.y + i, Color(255, 0, 0));
						else if (_Amap.Collider(pos.x, pos.y + i) == identitys[j] && object->id != identitys[j]) {
							for (i32 k = 0; k < object->ignore.size(); ++k) {
								if (object->ignore[k] == identitys[j])
									return { nullptr, (i16)dir };
							}
							return { (Master*)ptrs[j], --i };
						}
			return { nullptr, (i16)dir };
		}
		dir *= -1;
		for (; i <= dir; ++i)		//do this for all other code blocks
			for (i32 j = 0; j < identitys.size(); ++j)
				if (_debug)
					_Amap.Render(pos.x, pos.y - i, Color(255, 0, 0));
				else if (_Amap.Collider(pos.x, pos.y - i) == identitys[j] && object->id != identitys[j]) {
					for (i32 k = 0; k < object->ignore.size(); ++k) {
						if (object->ignore[k] == identitys[j])
							return { nullptr, (i16)dir };
					}
					return { (Master*)ptrs[j], --i };
				}	
		return { nullptr, (i16)dir };

	case Axis::Both:
		Error("Both axes are not valid. Change either to X or Y");
	}
}

//
//	Master
//
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

sur::Vec2 sur::Master::MovQueue(Vec2f direction)
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
	return { (i32)direction.x , (i32)direction.y};
}

void sur::Master::Move(sur::Vec2f direction, bool detect)
{
	auto cbcall = [&]() -> i32 {
		std::sort(packs->begin(), packs->end(), [](const auto& f, const auto& s)
			{
				return f.steps < s.steps;
			});
		assert(packs->size() < 1, 0);
		CollisionPackage cp = packs->at(0);
		if (cp.ptr != nullptr) {
			if (callback != nullptr)
				callback(this, cp.ptr);
			if (cp.ptr->callback != nullptr)
				cp.ptr->callback(cp.ptr, this);
		}
		i32 steps = packs->at(0).steps;
		packs->clear();
		return steps;
	};
	Vec2 newdirection = MovQueue(direction);
	assert(newdirection == Vec2(0, 0) || this->GetName() == "invalid");
	if (detect) {
		if (newdirection.x > 0) {
			for (i32 i = position.y; i < position.y + size.y; ++i) {
				packs->push_back(CheckCollision(this, Vec2(position.x + size.x, i), newdirection.x, Axis::X));
			}
			position.x += cbcall();
		}
		if (newdirection.x < 0) {
			for (i32 i = position.y; i < position.y + size.y; ++i) {
				packs->push_back(CheckCollision(this, Vec2(position.x, i), newdirection.x, Axis::X));
			}
			position.x -= cbcall();
		}
		if (newdirection.y > 0) {
			for (i32 i = position.x; i < position.x + size.x; ++i) {
				packs->push_back(CheckCollision(this, Vec2(i, position.y + size.y), newdirection.y, Axis::Y));
			}
			position.y += cbcall();
		}
		if (newdirection.y < 0) {
			for (i32 i = position.x; i < position.x + size.x; ++i) {
				packs->push_back(CheckCollision(this, Vec2(i, position.y), newdirection.y, Axis::Y));
			}
			position.y -= cbcall();
		}
		return;
	}
	position += newdirection;
}
//
//	Render
//
void sur::Render::ClearScreenBuffer()
{
	if(FillBackground)
		std::fill(_map.RenderMap, _map.RenderMap + _window_size.x * _window_size.y, bg);	
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
sur::Rectangle::Rectangle(Vec2 position, Vec2 size, Color color, const std::string& name, i32 id, bool canrotate,
	const std::vector<int>& ignoreids, cb_ptr<Master*> callback)
	:color(color), Master(name,id, position, size, callback)
{
	ignore = ignoreids;
	type = Type::Rectangle;
	identitys.push_back(id);
	ptrs.push_back(this);
}

void sur::Rectangle::Bind(bool Render,bool Collider)
{
	auto OutOfScreenCheck = [&]() -> bool {
		return (position.x >= _window_size.x || position.y >= _window_size.y ||
			position.x + size.x < 0 || position.y + size.y < 0) ? true : false;
	};
	if (OutOfScreenCheck()) return;
	for (i32 i = position.y; i < position.y + size.y; i++)
		for (i32 j = position.x; j < position.x + size.x; j++) {
			if (Render)
				_Amap.Render(j, i, color);
			if (Collider)
				_Amap.Collider(j - CO, i - CO, id);
		}
}

void sur::Rectangle::Rotate(sur::Vec2 origin, i32 Angle)
{

}

//
//	Line
//
sur::Line::Line(Vec2 start, Vec2 end, Color color, const std::string& name, i32 id, const std::vector<int>& ignoreids,
	cb_ptr<Master*> callback)
	: start(start), end(end), color(color), Master(name, id, callback)
{
	ignore = ignoreids;
	type = Type::Line;
	identitys.push_back(id);
	ptrs.push_back(this);
}

void sur::Line::Bind(bool Render, bool Collider)
{
	Vec2 end = this->end;
	Vec2 start = this->start;
	if (this->start.y > this->end.y || this->start.x > this->end.x) {
		std::swap(start.y, end.y);
		std::swap(start.x, end.x);
	}
	if (start.x == end.x) {
		for (i32 i = start.y; i < end.y; ++i) {
			if (Render)
				_Amap.Render(start.x, i, color);
			if (Collider)
				_Amap.Collider(start.x, i, id);
		}
		return;
	}
	if (start.y == end.y) {
		for (i32 i = start.x; i < end.x; ++i) {
			if (Render)
				_Amap.Render(i, start.y, color);
			if (Collider)
				_Amap.Collider(i, start.y, id);
		}
		return;
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
				_Amap.Render(i, tempy, color);
			if(Collider)
				_Amap.Collider(i - CO, tempy - CO, id);	
			while (counter >= countcounter) {
				tempy++;
				if (Render)
					_Amap.Render(i, tempy, color);
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
				_Amap.Render(i, tempy, color);
			if (Collider)
				_Amap.Collider(i - CO, tempy - CO, id);
			while (counter >= countcounter) {
				tempy--;
				if (Render)
					_Amap.Render(i, tempy, color);
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
					_Amap.Render(tempx, i, color);
				if(Collider)
					_Amap.Collider(tempx - CO, i - CO, id);
				while (counter >= countcounter) {
					tempx--;
					if (Render)
						_Amap.Render(tempx, i, color);
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
sur::Shape::Shape(Color color, const std::string& name, i32 id, const std::vector<int>& ignoreids,
	cb_ptr<Master*> callback) : color(color)
{
	ignore = ignoreids;
	this->name = name;
	type = Type::Shape;
	identitys.push_back(id);
	ptrs.push_back(this);
	this->id = id;
}

void sur::Shape::Gen()
{
	for (i32 i = 0; i < vec->size() - 1; ++i) {
		lines->push_back(new Line(vec->at(i), vec->at(i + 1), color, "ShapeLine" + std::to_string(i), id, ignore));
	}
}

void sur::Shape::SetPosition(i32 index, sur::Vec2 position) {
	++index;
	assert(index > lines->size() + 1 || index < 1);
	if (index == 1) {
		lines->at(index - 1)->Start(position);
		return;
	}
	if (index == lines->size() + 1) {
		lines->at(index - 2)->End(position);
		return;
	}
	lines->at(index - 1)->Start(position);
	lines->at(index - 2)->End(position);
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
	point.y = _window_size.y - point.y;
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

bool sur::Input::Keyboard::KeyDown(Keys::Keys key) 
{	
	if (GetAsyncKeyState(key)) {
		if (pressed != key) {
			pressed = key;
			return true;
		}
		return false;
	}
	else {
		pressed = Keys::Keys::None;
		return false;
	}
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

