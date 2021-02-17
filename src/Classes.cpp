

#include "Classes.h"

extern sur::Map_Analyses _Amap;
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
	bi.bmiHeader.biWidth = _window_size.y;
	bi.bmiHeader.biHeight = _window_size.x;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 32;
	bi.bmiHeader.biCompression = BI_RGB;
	sleep_for(milliseconds(Wait));
	SetDIBitsToDevice(dc, 0, 0, _window_size.y, _window_size.x, 0, 0, 0, _window_size.x, _map.RenderMap, &bi, 0);
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

//
//	Rectangle
//
void sur::Rectangle::Bind(bool Collider)
{
	for (int i = position.y; i < position.y + size.y; i++) {
		for (int j = position.x; j < position.x + size.x; j++) {
			_Amap.Render(j, i, color.ToCOLORREF());
			_Amap.Collider(j, i, id);
		}
	}
}

void sur::Rectangle::Id()
{
	id = Hash(*this, name);
	identitys.push_back(id);
	idindex = identitys.size();
}

void sur::Rectangle::Move(sur::Vec2 direction)
{
	int CurMove = 0;
	if (direction.y > 0) {
		for (int a = 1; a <= direction.y; a++) {
			for (int i = position.x; i < position.x + size.x; i++) {
				if (i - a <= 0) {
					break;							//Perfekt (99%)
				}
				for (int j = 0; j < identitys.size(); j++) {
					if (_Amap.Collider(position.y - a, i) == identitys[j]) {
						goto dir1;
					}
				}
			}
			CurMove = a;
		}
	dir1:
		position.y -= CurMove;
	}
	if (direction.x > 0 ) {
		for (int a = 1; a <= direction.x; a++) {
			for (int i = position.y; i < position.y + size.y; i++) {
				if (i - a <= 0) {
					break;							//Perfekt (99%)
				}
				l(_Amap.Collider(i, position.x - a));
				for (int j = 0; j < identitys.size(); j++) {
					if (_Amap.Collider(i, position.x - a) == identitys[j]) {
						goto dir2;
					}
				}
			}
			CurMove = a;
		}
	dir2:
		position.x += CurMove;
	}
	if (direction.y < 0) {
		direction.y *= -1;
		for (int a = 1; a <= direction.y; a++) {
			for (int i = position.x; i < position.x + size.x; i++) {
				if (i - a <= 0) {
					break;							//Perfekt (99%)
				}
				for (int j = 0; j < identitys.size(); j++) {
					if (_Amap.Collider(position.y + size.y + a - 1, i) == identitys[j]){
						goto dir3;
					}
				}
			}
			CurMove = a;
		}
	dir3:
		position.y += CurMove;
	}
	if (direction.x < 0) {
		direction.x *= -1;
		for (int a = 1; a <= direction.x; a++) {
			for (int i = position.y; i < position.y + size.y; i++) {
				if (i - a <= 0) {
					break;							//Perfekt (99%)
				}
				for (int j = 0; j < identitys.size(); j++) {
					if (_Amap.Collider(i, position.x + size.x + a - 1) == identitys[j]) {
						goto dir4;
					}
				}
			}
			CurMove = a;
		}
	dir4:
		position.x -= CurMove;
	}

}
//
//	Line
//
void sur::Line::Bind()
{
	int lcounter = 0;
	sur::Vec2 end = this->end;
	sur::Vec2 start = this-> start;
	if (this->start.y > this->end.y && this->start.x > this->end.x) {
		std::swap(start.y, end.y);
		std::swap(start.x, end.x);
	}
	int Dx, Dy;
	float RunsThrough;
	Dx = end.x - start.x;
	Dy = end.y - start.y;
	RunsThrough = (float)Dy / (float)Dx;
	if (RunsThrough >= 0) {
		int tempy = start.y;
		float counter = 0.0f;
		int countcounter = 1;
		for (int i = start.x; i <= end.x; i++) {
			_Amap.Render(i, tempy, color.ToCOLORREF());
			while (counter >= countcounter) {
				tempy++;
				_Amap.Render(i, tempy, color.ToCOLORREF());
				countcounter++;
			}
			counter += RunsThrough;
		}
	}
	else {
		RunsThrough *= -1;
		int tempy = start.y;
		float counter = 0.0f;
		int countcounter = 1;
		bool runned = false;
		for (int i = start.x; i <= end.x; i++) {
			_Amap.Render(i, tempy, color.ToCOLORREF());
			while (counter >= countcounter) {
				tempy--;
				_Amap.Render(i, tempy, color.ToCOLORREF());
				countcounter++;
			}
			runned = true;	
			counter += RunsThrough;
		}
		if (!runned) {
			RunsThrough = (float)Dx / (float)Dy;
			RunsThrough *= -1;
			int tempx = start.x;
			for (int i = start.y; i <= end.y; i++) {
				_Amap.Render(tempx, i, color.ToCOLORREF());
				while (counter >= countcounter) {
					tempx--;
					_Amap.Render(tempx, i, color.ToCOLORREF());
					countcounter++;
				}
				counter += RunsThrough;
			}
		}
	}
}
//
//	Input
//

//	Mouse
sur::Vec2 sur::Input::Mouse::Position()
{
	POINT point;
	GetCursorPos(&point);
	ScreenToClient(_hwnd, &point);
	return{ point.x, point.y };
}

bool sur::Input::Mouse::LClick()
{
	if (GetAsyncKeyState(VK_LBUTTON))
		return true;
	return false;
}

bool sur::Input::Mouse::RClick()
{
	if (GetAsyncKeyState(VK_RBUTTON))
		return true;
	return false;
}

// Keyboard
bool sur::Input::Keyboard::Key(Keys key)
{
	if (GetAsyncKeyState(key))
		return true;
	return false;
}
//
//	Map_Analyses
//
void sur::Map_Analyses::operator()(sur::Maps map, sur::Vec2 size)
{
	Collider(map.ColliderMap, size);
	Trigger(map.ColliderMap, size);
	Render(map.RenderMap, size);
}

void sur::Map_Analyses::operator()(int* cptr, int* tptr, DWORD* rptr, sur::Vec2 size)
{
	Collider(cptr, size);
	Trigger(tptr, size);
	Render(rptr, size);
}
