

#include "Classes.h"


std::vector<i32> identitys;
std::vector<void*> ptrs;


extern sur::Map_Analyses _Amap;
extern std::vector<i32> trigger_identitys;
extern std::vector<void*> trigger_ptrs;

//
//	Master
//
sur::Vec2 sur::Master::rot(Vec2 pos, Vec2 origin, i32 Angle)
{
	sur::Vec2 dist(pos - origin);
	return 	sur::Vec2((i32)(dist.x * cos(Angle * PI / 180) - dist.y * sin(Angle * PI / 180)),
		(i32)(dist.x * sin(Angle * PI / 180) + dist.y * cos(Angle * PI / 180))) + origin;
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


//void sur::Master::Move(sur::Vec2f direction, bool detect)
//{
//	Vec2 newdirection = MovQueue(direction);
//	assert(newdirection == Vec2(0, 0) || this->GetName() == "invalid");
//
//	if (!detect) position += newdirection;
//
//	bool dirXpos = (newdirection.x >= 0) ? true : false;
//
//	bool dirYpos = (newdirection.y >= 0) ? true : false;
//
//	i32 contentX = 0, contentY = 0;
//
//	if (dirXpos) {
//	jmp0:
//		for (i32 i = 0; i < CollisionPos.size(); ++i) {
//			 contentX = _Amap.Collider(CollisionPos.at(i).x + newdirection.x, CollisionPos.at(i).y);
//			for (i32 j = 0; j < ignore.size(); ++j)
//				if (contentX == ignore.at(j))
//					contentX = 0;	//So it ignores the collision
//			if (contentX != 0 && contentX != this->id) {
//				--newdirection.x;
//				if (newdirection.x == 0) break;
//				goto jmp0;
//			}
//		}
//	}
//	else {
//	jmp1:
//		for (i32 i = 0; i < CollisionPos.size(); ++i) {
//			contentX = _Amap.Collider(CollisionPos.at(i).x + newdirection.x, CollisionPos.at(i).y);
//			for (i32 j = 0; j < ignore.size(); ++j)
//				if (contentX == ignore.at(j))
//					contentX = 0;	//So it ignores the collision
//			if (contentX != 0 && contentX != this->id) {
//				++newdirection.x;
//				if (newdirection.x == 0) break;
//				goto jmp1;
//			}
//		}
//	}
//	if (dirYpos) {
//	jmp2:
//		for (i32 i = 0; i < CollisionPos.size(); ++i) {
//			contentY = _Amap.Collider(CollisionPos.at(i).x, CollisionPos.at(i).y + newdirection.y);
//			for (i32 j = 0; j < ignore.size(); ++j)
//				if (contentY == ignore.at(j))
//					contentY = 0;	//So it ignores the collision
//			if (contentY != 0 && contentY != this->id) {
//				--newdirection.y;
//				if (newdirection.y == 0) break;
//				goto jmp2;
//			}
//		}
//	}
//	else {
//	jmp3:
//		for (i32 i = 0; i < CollisionPos.size(); ++i) {
//			contentY = _Amap.Collider(CollisionPos.at(i).x, CollisionPos.at(i).y + newdirection.y);
//			for (i32 j = 0; j < ignore.size(); ++j)
//				if (contentY == ignore.at(j))
//					contentY = 0;	//So it ignores the collision
//			if (contentY != 0 && contentY != this->id) {
//				++newdirection.y;
//				if (newdirection.y == 0) break;
//				goto jmp3;
//			}
//		}
//	}
//
//	{
//		i32 iX = 0,iY = 0;
//		for (i32 i = 0; i < identitys.size(); ++i) {
//			if (contentX == identitys[i]) {
//				iX = i;
//			}
//		}
//		for (i32 i = 0; i < identitys.size(); ++i) {
//			if (contentY == identitys[i]) {
//				iY = i;
//			}
//		}
//		if (iX != 0 && contentX != this->id) {
//			if (callback != nullptr)
//				callback(this, (Master*)ptrs[iX]);
//			if (static_cast<Master*>(ptrs[iX])->callback != nullptr)
//				static_cast<Master*>(ptrs[iX])->callback((Master*)ptrs[iX], this);
//		}
//		if (iY != 0 && contentY != this->id) {
//			if (callback != nullptr)
//				callback(this, (Master*)ptrs[iY]);
//			if (static_cast<Master*>(ptrs[iY])->callback != nullptr)
//				static_cast<Master*>(ptrs[iY])->callback((Master*)ptrs[iY], this);
//		}
//	}
//	MoveInject(newdirection);
//}

void sur::Master::Move(sur::Vec2f direction, bool detect) {
	Vec2 newdirection = MovQueue(direction);
	assert(newdirection == Vec2(0, 0) || this->GetName() == "invalid");

	if (!detect) { position += newdirection; return; }

	bool dirXpos = (newdirection.x >= 0) ? true : false;

	bool dirYpos = (newdirection.y >= 0) ? true : false;

	i32 contentX = 0, contentY = 0;

	if (dirXpos) {	
		for (i32 c = 1; c <= newdirection.x; ++c) {
			for (i32 i = 0; i < CollisionPos.size(); ++i) {
				contentX = _Amap.Collider(CollisionPos.at(i).x + c, CollisionPos.at(i).y);
				for (i32 j = 0; j < ignore.size(); ++j)
					if (contentX == ignore.at(j))
						contentX = 0;	//So it ignores the collision
				if (contentX != 0 && contentX != this->id) {
					newdirection.x = --c;
					goto jmp0;
				}
			}
		}
	jmp0:;
	}
	else {
		for (i32 c = -1; c >= newdirection.x; --c) {
			for (i32 i = 0; i < CollisionPos.size(); ++i) {
				contentX = _Amap.Collider(CollisionPos.at(i).x + c, CollisionPos.at(i).y);
				for (i32 j = 0; j < ignore.size(); ++j)
					if (contentX == ignore.at(j))
						contentX = 0;	//So it ignores the collision
				if (contentX != 0 && contentX != this->id) {
					newdirection.x = ++c;
					goto jmp1;
				}
			}
		}
	jmp1:;
	}
	if (dirYpos) {
		for (i32 c = 1; c <= newdirection.y; ++c) {
			for (i32 i = 0; i < CollisionPos.size(); ++i) {
				contentY = _Amap.Collider(CollisionPos.at(i).x, CollisionPos.at(i).y + c);
				for (i32 j = 0; j < ignore.size(); ++j)
					if (contentY == ignore.at(j))
						contentY = 0;	//So it ignores the collision
				if (contentY != 0 && contentY != this->id) {
					newdirection.y = --c;
					goto jmp2;
				}
			}
		}
	jmp2:;
	}
	else {
		for (i32 c = -1; c >= newdirection.y; --c) {
			for (i32 i = 0; i < CollisionPos.size(); ++i) {
				contentY = _Amap.Collider(CollisionPos.at(i).x, CollisionPos.at(i).y + c);
				for (i32 j = 0; j < ignore.size(); ++j)
					if (contentY == ignore.at(j))
						contentY = 0;	//So it ignores the collision
				if (contentY != 0 && contentY != this->id) {
					newdirection.y = ++c;
					goto jmp3;
				}
			}
		}
	jmp3:;
	}

	{
		i32 iX = 0, iY = 0;
		for (i32 i = 0; i < identitys.size(); ++i) {
			if (contentX == identitys[i]) {
				iX = i;
			}
		}
		for (i32 i = 0; i < identitys.size(); ++i) {
			if (contentY == identitys[i]) {
				iY = i;
			}
		}
		if (iX != 0 && contentX != this->id) {
			if (callback != nullptr)
				callback(this, (Master*)ptrs[iX]);
			if (static_cast<Master*>(ptrs[iX])->callback != nullptr)
				static_cast<Master*>(ptrs[iX])->callback((Master*)ptrs[iX], this);
		}
		if (iY != 0 && contentY != this->id) {
			if (callback != nullptr)
				callback(this, (Master*)ptrs[iY]);
			if (static_cast<Master*>(ptrs[iY])->callback != nullptr)
				static_cast<Master*>(ptrs[iY])->callback((Master*)ptrs[iY], this);
		}
	}
	MoveInject(newdirection);
}

//
//	Render
//
void sur::Render::ClearScreenBuffer()
{
	if (FillBackground)
		memset(_map.RenderMap, bg, sizeof(Color) * (_window_size.x * _window_size.y));	
	memset(_map.ColliderMap, 0, sizeof(Color) * (_window_size.x * _window_size.y));
	memset(_map.TriggerMap, 0, sizeof(Color) * (_window_size.x * _window_size.y));
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

void sur::Rectangle::Bind(bool Render, bool Collider)
{
	auto OutOfScreenCheck = [&]() -> bool {
		return (position.x >= _window_size.x || position.y >= _window_size.y ||
			position.x + size.x < 0 || position.y + size.y < 0) ? true : false;
	};
	//if (OutOfScreenCheck()) return;	//needs a fix
	if (Render)
		for (i32 i = 0; i < size.y; i++)
			for (i32 j = 0; j < size.x; j++)
				_Amap.Render(matrix.mulitplyWithVector(Vec2(j, i )) + position, color);
	if (!Collider) return;
	CollisionPos.clear();
	for (i32 i = 0; i < size.x; i++) {
		{
			sur::Vec2 tmp(matrix.mulitplyWithVector(Vec2(i, 0 )) + position);
			CollisionPos.push_back(tmp);
			_Amap.Collider(tmp, id);
		}
		{
			sur::Vec2 tmp(matrix.mulitplyWithVector(Vec2(i, size.y )) + position);
			CollisionPos.push_back(tmp);
			_Amap.Collider(tmp, id);
		}
	}
	for (i32 i = 0; i < size.y; i++) {
		{
			sur::Vec2 tmp(matrix.mulitplyWithVector(Vec2(0, i )) + position);
			CollisionPos.push_back(tmp);
			_Amap.Collider(tmp, id);
		}
		{
			sur::Vec2 tmp(matrix.mulitplyWithVector(Vec2(size.x, i )) + position);
			CollisionPos.push_back(tmp);
			_Amap.Collider(tmp, id);
		}
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
	auto Write = [=](i32 x, i32 y) {
		sur::Vec2 tmp = matrix.mulitplyWithVector({ (f32)(x - position.x), (f32)(y - position.y) }) + position;
		if (Render) {
			_Amap.Render(tmp, color);
		}
		if (Collider) {
			CollisionPos.push_back(tmp);
			_Amap.Collider(tmp, id);
		}
	};
	if (Collider) CollisionPos.clear();
	Vec2 end = this->end;
	Vec2 start = this->start;
	if (this->start.y > this->end.y || this->start.x > this->end.x) {
		std::swap(start.y, end.y);
		std::swap(start.x, end.x);
	}
	position = { start.x,start.y };
	if (start.x == end.x) {
		for (i32 i = start.y; i < end.y; ++i) {
			Write(start.x, i);
		}
		return;
	}
	if (start.y == end.y) {
		for (i32 i = start.x; i < end.x; ++i) {
			Write(i, start.y);
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
			Write(i, tempy);
			while (counter >= countcounter) {
				tempy++;
				Write(i, tempy);
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
			Write(i, tempy);
			while (counter >= countcounter) {
				tempy--;
				Write(i, tempy);
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
				Write(tempx,i);
				while (counter >= countcounter) {
					tempx--;
					Write(tempx, i);
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
		lines->push_back(new Line(vec->at(i), vec->at(i + 1), color, name + "ShapeLine" + std::to_string(i), id, ignore));
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

void sur::Map_Analyses::operator()(i32* cptr, i32* tptr, Color* rptr, sur::Vec2 size)
{
	Collider(cptr, size);
	Trigger(tptr, size);
	Render(rptr, size);
}

