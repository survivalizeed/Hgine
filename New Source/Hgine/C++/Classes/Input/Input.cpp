

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

bool sur::Input::Keyboard::KeyHeld(Keys key)
{
	if (GetAsyncKeyState(key) & 0x8000)
		return true;
	return false;
}

bool sur::Input::Keyboard::KeyPress(Keys key)
{
	bool space = false;
	if (key == Keys::SPACE)
		space = true;
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (space && pressed[26] != key)
		{
			pressed[26] = key;
			return true;
		}
		else if (!space && pressed[static_cast<i32>(key) - 65] != key)
		{
			pressed[static_cast<i32>(key) - 65] = key;
			return true;
		}
		return false;
	}
	else
	{
		if (space)
			pressed[26] = Keys::None;
		else
			pressed[static_cast<i32>(key) - 65] = Keys::None;
		return false;
	}
}
