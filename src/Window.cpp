#include "includes.h"

WNDCL wc;


LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)	//CALLBACK required for x86
{
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

void win(const char* Name,int params) {

	HINSTANCE hInstance = GetModuleHandle(0);
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
	MSG Msg;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndEx
void Window(const char* Name,int params) {
	std::thread wins(win,Name,params);
	wins.detach();
	Sleep(100);
}
