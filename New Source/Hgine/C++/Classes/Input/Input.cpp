

#include "Input.h"

sur::Vec2f sur::Input::Mouse::Position()
{
	POINT point;
	GetCursorPos(&point);
	ScreenToClient(_window_hwnd, &point);
	if (point.x < 0 || point.y < 0)
		return { 0, 0 };
	if (point.x > _window_size.x - 1 || point.y > _window_size.y - 1)
		return STA(Vec2(_window_size.x - 1, _window_size.y - 1));
	point.y = _window_size.y - point.y;
	return STA(Vec2(point.x, point.y));
}

bool sur::Input::Mouse::LClick()
{
	if (GetKeyState(VK_LBUTTON) & 0x8000)
		return true;
	return false;
}

bool sur::Input::Mouse::RClick()
{
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000)
		return true;
	return false;
}
