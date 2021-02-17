#include "includes.h"

WNDCLASSEX wc;


LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

void win() {

	HINSTANCE hInstance = GetModuleHandle(0);
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
	MSG Msg;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "CLASS";
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wc);
	SetWindowLong(_hwnd, GWL_STYLE, GetWindowLong(_hwnd, GWL_STYLE) & ~WS_MAXIMIZEBOX);
	_hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, "CLASS", "Test", WS_POPUP | WS_CAPTION | WS_BORDER, CW_USEDEFAULT, CW_USEDEFAULT, _window_size.x, _window_size.y, NULL, NULL, hInstance, NULL);
	ShowWindow(_hwnd, SW_SHOW);
	UpdateWindow(_hwnd);
	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	Gdiplus::GdiplusShutdown(gdiplusToken);
}


void Window() {
	std::thread wins(win);
	wins.detach();
	Sleep(100);
}