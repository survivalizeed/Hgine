

#include "Renderer.h"

namespace sur
{
	class GameObject;
}

sur::Renderer::Renderer(Color background, bool fillBackground, f32 ambient_light, bool use_light)
{
	_background = background;
	this->fillBackground = fillBackground;
	dc = GetDC(_window_hwnd);
	_ambient_light = ambient_light;
	_use_light = use_light;
}

void sur::Renderer::Clear() const
{
	if (fillBackground)
		std::fill(_render_buffer, _render_buffer + _window_size.x * _window_size.y, _background);
}

void sur::Renderer::Render()
{
	BITMAPINFO bi = { 0 };
	bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bi.bmiHeader.biWidth = _window_size.x;
	bi.bmiHeader.biHeight = _window_size.y;
	bi.bmiHeader.biPlanes = 1;
	bi.bmiHeader.biBitCount = 32;
	bi.bmiHeader.biCompression = BI_RGB;
	SetDIBitsToDevice(dc, 0, 0, _window_size.x, _window_size.y, 0, 0, 0, _window_size.x, _render_buffer, &bi, 0);
	frameCounter++;
}

void sur::Renderer::FPS()
{
	auto fps_counter = [&]() {
		std::string Buffer;
		char* title = new char[100];
		GetWindowTextA(_window_hwnd, title, 100);
		while (true)
		{
			sleep_for(seconds(1));
			Buffer += title;
			Buffer += " FPS: ";
			Buffer += std::to_string(frameCounter);
			SetWindowTextA(_window_hwnd, Buffer.c_str());
			Buffer = "";
			frameCounter = 0;
		}
	};
	std::thread actual_counter(fps_counter);
	actual_counter.detach();
}

void sur::Renderer::DebugConsole(bool show) const
{
	if (!show)
		ShowWindow(GetConsoleWindow(), SW_HIDE);
}
