

#include "Input.h"

std::optional<sur::Vec2f> sur::Input::Mouse::Position()
{
	POINT point;
	GetCursorPos(&point);
	ScreenToClient(_window_hwnd, &point);
	if (point.x < 0 || point.y < 0)
		return std::nullopt;
	if (point.x > _window_size.x - 1 || point.y > _window_size.y - 1)
		return std::nullopt;
	point.y = _window_size.y - point.y;
	return STA(Vec2(point.x, point.y) - _camera_offset);
}

bool sur::Input::Mouse::LClickHeld()
{
	if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && GetForegroundWindow() == _window_hwnd)
		return true;
	return false;
}

bool sur::Input::Mouse::RClickHeld()
{
	if (GetAsyncKeyState(VK_RBUTTON) & 0x8000 && GetForegroundWindow() == _window_hwnd)
		return true;
	return false;
}

bool sur::Input::Mouse::LClickPress()
{
	if (GetKeyState(VK_LBUTTON) & 0x8000 && GetForegroundWindow() == _window_hwnd) {
		if (!mClick[0]) {
			mClick[0] = true;
			return true;
		}
		return false;
	}
	else {
		mClick[0] = false;
		return false;
	}	
}

bool sur::Input::Mouse::RClickPress()
{
	if (GetKeyState(VK_RBUTTON) & 0x8000 && GetForegroundWindow() == _window_hwnd) {
		if (!mClick[1]) {
			mClick[1] = true;
			return true;
		}
		return false;
	}
	else {
		mClick[1] = false;
		return false;
	}
}

bool sur::Input::Keyboard::KeyHeld(Key key)
{
	if (GetAsyncKeyState(key) & 0x8000 && GetForegroundWindow() == _window_hwnd)
		return true;
	return false;
}

bool sur::Input::Keyboard::KeyPress(Key key)
{
	if (GetAsyncKeyState(key) & 0x8000 && GetForegroundWindow() == _window_hwnd)
	{
		if (key >= 0x41 && key <= 0x5A) {
			if (charPressed[static_cast<i32>(key) - 65] != key)
			{
				charPressed[static_cast<i32>(key) - 65] = key;
				return true;
			}
		}
		else if (key >= 0x30 && key <= 0x39) {
			if (numericePressed[static_cast<i32>(key) - 48] != key) {
				numericePressed[static_cast<i32>(key) - 48] = key;
				return true;
			}
		}
		else if (key >= 0x60 && key <= 0x69) {
			if (numNumericePressed[static_cast<i32>(key) - 96] != key) {
				numNumericePressed[static_cast<i32>(key) - 96] = key;
				return true;
			}
		}
		else {
			if (key == Space && miscPressed[0] != key) {
				miscPressed[0] = key;
				return true;
			}
			if (key == ArLeft && miscPressed[1] != key) {
				miscPressed[1] = key;
				return true;
			}
			if (key == ArUp && miscPressed[2] != key) {
				miscPressed[2] = key;
				return true;
			}
			if (key == ArRight && miscPressed[3] != key) {
				miscPressed[3] = key;
				return true;
			}
			if (key == ArDown && miscPressed[4] != key) {
				miscPressed[4] = key;
				return true;
			}
			if (key == Escape && miscPressed[5] != key) {
				miscPressed[5] = key;
				return true;
			}
			if (key == Enter && miscPressed[6] != key) {
				miscPressed[6] = key;
				return true;
			}
			if (key == Shift && miscPressed[7] != key) {
				miscPressed[7] = key;
				return true;
			}
			if (key == Control && miscPressed[8] != key) {
				miscPressed[8] = key;
				return true;
			}
			if (key == Back && miscPressed[9] != key) {
				miscPressed[9] = key;
				return true;
			}
		}
		return false;
	}
	else
	{
		if (key >= 0x41 && key <= 0x5A) {
			charPressed[static_cast<i32>(key) - 65] = None;
		}
		else if (key >= 0x30 && key <= 0x39) {
			numericePressed[static_cast<i32>(key) - 48] = None;
		}
		else if (key >= 0x60 && key <= 0x69) {
			numNumericePressed[static_cast<i32>(key) - 96] = None;
		}
		else {
			if (key == Space)
				miscPressed[0] = None;
			if (key == ArLeft)	
				miscPressed[1] = None;
			if (key == ArUp)		
				miscPressed[2] = None;
			if (key == ArRight) 
				miscPressed[3] = None;
			if (key == ArDown)	
				miscPressed[4] = None;
			if (key == Escape)	 
				miscPressed[5] = None;
			if (key == Enter)	 
				miscPressed[6] = None;
			if (key == Shift)	 
				miscPressed[7] = None;
			if (key == Control)	
				miscPressed[8] = None;
			if (key == Back)	 
				miscPressed[9] = None;
		}
		return false;
	}
}
