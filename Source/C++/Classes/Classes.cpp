

#include "Classes.h"


std::vector<i32> identitys;
std::vector<void*> ptrs;
std::vector<sur::Light*> lights;


extern sur::Map_Analyses _Amap;
extern std::vector<i32> trigger_identitys;
extern std::vector<void*> trigger_ptrs;

//
//	Master
//
sur::Vec2 sur::Master::rot(Vec2 pos, Vec2 origin, i32 angle)
{
	sur::Vec2 dist(pos - origin);
	return 	sur::Vec2((i32)(dist.x * cos(angle * PI / 180) - dist.y * sin(angle * PI / 180)),
		(i32)(dist.x * sin(angle * PI / 180) + dist.y * cos(angle * PI / 180))) + origin;
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

sur::Vec2 sur::Master::Move(sur::Vec2f direction, bool detect) {
	Vec2 newdirection = MovQueue(direction);
	assert(newdirection == Vec2(0, 0) || this->GetName() == "invalid", Vec2(0,0));

	if (!detect) { MoveInject(newdirection); return newdirection; }

	bool dirXpos = (newdirection.x >= 0) ? true : false;

	bool dirYpos = (newdirection.y >= 0) ? true : false;

	volatile i32 contentX = 0, contentY = 0;

	Vec2 dirStor = newdirection;
	Vec2 actualMoveX, actualMoveY;

	if (dirXpos) {	
		for (i32 c = 1; c <= newdirection.x; ++c) {
			for (i32 i = 0; i < CollisionPos.size(); ++i) {
				contentX = _Amap.Collider(CollisionPos.at(i).x + c, CollisionPos.at(i).y);
				for (i32 j = 0; j < ignore.size(); ++j)
					if (contentX == ignore.at(j))
						contentX = 0;	//So it ignores the collision
				if (contentX != 0 && contentX != this->id) {
					for (i32 j = 0; j < push.size(); ++j)
						if (contentX == push[j])
							for (i32 a = 0; a < identitys.size(); ++a)
								if (contentX == identitys[a]) {
									actualMoveX(static_cast<sur::Master*>(ptrs[a])->Move({ f32(dirStor.x - (--c)),0 }, true));
									newdirection.x = (--c) + actualMoveX.x;
									goto jmp0;
								}
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
					for (i32 j = 0; j < push.size(); ++j)
						if (contentX == push[j])
							for (i32 a = 0; a < identitys.size(); ++a)
								if (contentX == identitys[a]) {
									actualMoveX(static_cast<sur::Master*>(ptrs[a])->Move({ f32(dirStor.x - (++c)),0 }, true));
									newdirection.x = (++c) + actualMoveX.x;
									goto jmp1;
								}
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
					for (i32 j = 0; j < push.size(); ++j)
						if (contentY == push[j])
							for (i32 a = 0; a < identitys.size(); ++a)
								if (contentY == identitys[a]) {
									actualMoveY(static_cast<sur::Master*>(ptrs[a])->Move({ 0, f32(dirStor.y - (--c)) }, true));
									newdirection.y = (--c) + actualMoveY.y;
									goto jmp2;
								}
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
					for (i32 j = 0; j < push.size(); ++j)
						if (contentY == push[j])
							for (i32 a = 0; a < identitys.size(); ++a)
								if (contentY == identitys[a]) {
									actualMoveY(static_cast<sur::Master*>(ptrs[a])->Move({ 0, f32(dirStor.y - (++c)) }, true));
									newdirection.y = (++c) + actualMoveY.y;
									goto jmp3;
								}
					newdirection.y = ++c;
					goto jmp3;
				}
			}
		}
	jmp3:;
	}

	{
		volatile i32 iX = 0, iY = 0;
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
	return newdirection;
}

//
//	Render
//
void sur::Render::ClearScreenBuffer()
{
	if (FillBackground)
		memset(_map.RenderMap, bg, sizeof(Color) * (_window_size.x * _window_size.y));	
	memset(_map.ColliderMap, 0, sizeof(i32) * (_window_size.x * _window_size.y));
	memset(_map.TriggerMap, 0, sizeof(i32) * (_window_size.x * _window_size.y));
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
		restricted::shapes->at(i)->Move(direction);
	}
	for (i32 i = 0; i < restricted::trigger_rectangles->size(); i++) {
		restricted::trigger_rectangles->at(i)->Move(direction);
	}
}
//
//	Rectangle
//
sur::Rectangle::Rectangle(Vec2f position, Vec2f size, Color color, std::string_view name, i32 id,
	const std::vector<i32>& ignoreids, const std::vector<i32>& push, cb_ptr<Master*> callback) 
	: Master(name,id,color, position, size, callback)
{
	this->push = push;
	ignore = ignoreids;
	type = Type::Rectangle;
	identitys.push_back(id);
	ptrs.push_back(this);
}



void sur::Rectangle::Bind(bool Render, bool Collider)
{
	auto OutOfScreenCheck = [&]() -> bool {
		return (position.x >= _window_size.x || position.y >= _window_size.y ||
			size.x < 0 ||  size.y < 0) ? true : false;
	};
	if (OutOfScreenCheck()) return;	//needs a fix
	if (Render)
		for (i32 i = 0; i < size.y - position.y; i++)
			for (i32 j = 0; j < size.x - position.x; j++)
				_Amap.Render(matrix.multiplyWithVector(Vec2(j, i )) + position, color);
	if (!Collider) return;
	CollisionPos.clear();
	for (i32 i = 0; i < size.x - position.x; i++) {
		{
			sur::Vec2 tmp(matrix.multiplyWithVector(Vec2(i, 0 )) + position);
			CollisionPos.push_back(tmp);
			if (_debug)
				_Amap.Render(tmp, Color(255, 0, 0));
			_Amap.Collider(tmp, id);
		}
		{
			sur::Vec2 tmp(matrix.multiplyWithVector(Vec2(i, size.y - position.y )) + position);
			CollisionPos.push_back(tmp);
			if(_debug)
				_Amap.Render(tmp, Color(255,0,0));
			_Amap.Collider(tmp, id);
		}
	}
	for (i32 i = 0; i < size.y - position.y; i++) {
		{
			sur::Vec2 tmp(matrix.multiplyWithVector(Vec2(0, i )) + position);
			CollisionPos.push_back(tmp);
			if (_debug)
				_Amap.Render(tmp, Color(255, 0, 0));
			_Amap.Collider(tmp, id);
		}
		{
			sur::Vec2 tmp(matrix.multiplyWithVector(Vec2(size.x - position.x, i )) + position);
			CollisionPos.push_back(tmp);
			if (_debug)
				_Amap.Render(tmp, Color(255, 0, 0));
			_Amap.Collider(tmp, id);
		}
	}
}


//
//	Line
//
sur::Line::Line(Vec2f start, Vec2f end, Color color, std::string_view name, i32 id, const std::vector<int>& ignoreids,
	cb_ptr<Master*> callback)
	: start(ATS(start)), end(ATS(end)), Master(name, id, color, callback)
{
	ignore = ignoreids;
	type = Type::Line;
	identitys.push_back(id);
	ptrs.push_back(this);
}

void sur::Line::Bind(bool Render, bool Collider)
{
	auto Write = [=](i32 x, i32 y) {
		if (Render) {
			_Amap.Render({ x,y }, color);
		}
		if (Collider) {
			CollisionPos.push_back({ x,y });
			_Amap.Collider({ x,y }, id);
		}
	};
	if (Collider) CollisionPos.clear();
	Vec2 end = this->end;
	Vec2 start = this->start;
	if (this->start.y > this->end.y || this->start.x > this->end.x) {
		std::swap(start.y, end.y);
		std::swap(start.x, end.x);
	}
	start = matrix.multiplyWithVector(start);	// Beta
	end = matrix.multiplyWithVector(end);	// Beta
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
sur::Shape::Shape(Color color, std::string_view name, i32 id, const std::vector<int>& ignoreids,
	cb_ptr<Master*> callback) : Master(name, id, color, callback)
{
	ignore = ignoreids;
	type = Type::Shape;
	identitys.push_back(id);
	ptrs.push_back(this);
}

void sur::Shape::Gen()
{
	for (i32 i = 0; i < vec->size() - 1; ++i) {
		lines->push_back(new Line(vec->at(i), vec->at(i + 1), color, name + "ShapeLine" + std::to_string(i), id, ignore));
	}
}

void sur::Shape::SetPosition(i32 index, Vec2f position) {
	++index;
	assert(index > lines->size() + 1 || index < 1);
	if (index == 1) {
		lines->at(index - 1)->Start(ATS(position));
		return;
	}
	if (index == lines->size() + 1) {
		lines->at(index - 2)->End(ATS(position));
		return;
	}
	lines->at(index - 1)->Start(ATS(position));
	lines->at(index - 2)->End(ATS(position));
}

void sur::Shape::Bind(bool Render, bool Collider)
{
	for (auto&& it : *lines)
		it->Bind(Render,Collider);
}

void sur::Shape::Move(sur::Vec2f direction)
{
	Vec2 newdirection = MovQueue(direction);
	assert(newdirection == Vec2(0, 0) || this->GetName() == "invalid");
	for (auto&& it : *lines) {
		it->Start(it->GetStart() + newdirection);
		it->End(it->GetEnd() + newdirection);
	}
}
//
//	Light
//
sur::Light::Light(Vec2f position, f32 radius, Color color, std::string_view name)
	: radius(radius)
{
	this->color = color;
	this->name = name;
	this->position = ATS(position);
	lights.push_back(this);
}

//
//	Input
//

//	Mouse
sur::Vec2f sur::Input::Mouse::Position() const
{
	POINT point;
	GetCursorPos(&point);
	ScreenToClient(_hwnd, &point);
	if (point.x < 0 || point.y < 0)
		return { 0,0 };
	if (point.x > _window_size.x - 1 || point.y > _window_size.y - 1)
		return STA(Vec2(_window_size.x - 1, _window_size.y - 1));
	point.y = _window_size.y - point.y;
	return STA(Vec2(point.x, point.y));
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
	bool space = false;
	if (key == Keys::Keys::SPACE)
		space = true;
	if (GetAsyncKeyState(key)) {
		if (space && pressed[26] != key) {
			pressed[26] = key;
			return true;
		}
		else if (!space && pressed[(i32)key - 65] != key) {		//Some ASCII calculations
			pressed[(i32)key - 65] = key;
			return true;
		}
		return false;
	}
	else {
		if (space)
			pressed[26] = Keys::Keys::None;
		else
			pressed[(i32)key - 65] = Keys::Keys::None;
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



