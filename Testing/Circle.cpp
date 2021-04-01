#include <iostream>
#include <cmath>
#include <windows.h>

HWND hwnd;
WNDCLASSEX wc;
COLORREF PBackgroundColor;
int PSx, PSy;
LRESULT WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hwnd, msg, wParam, lParam);
}


void Window() {
	HINSTANCE hInstance = GetModuleHandle(0);
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR gdiplusToken;
	Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, nullptr);
	HBRUSH hb = CreateSolidBrush(RGB(50, 50, 50));
	MSG Msg;
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = 0;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = hb;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"CLASS";
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	RegisterClassEx(&wc);
	SetWindowLong(hwnd, GWL_STYLE, GetWindowLong(hwnd, GWL_STYLE) & ~WS_MAXIMIZEBOX);
	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, L"CLASS", L"Test", WS_POPUP | WS_BORDER | WS_CAPTION, CW_USEDEFAULT, CW_USEDEFAULT, 500, 500, NULL, NULL, hInstance, NULL);
	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
	while (GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	Gdiplus::GdiplusShutdown(gdiplusToken);
}




typedef int i32;
struct Vec2 {

	i32 x = 0, y = 0;
	
	Vec2() = default;

	Vec2(i32 x, i32 y) : x(x), y(y) {}

	Vec2(const Vec2& vector2d) : x(vector2d.x), y(vector2d.y) {}

	inline Vec2 invert() { return { this->x * -1, this->y * -1 }; }
	inline float magnitude() { return (float)sqrt(pow(x, 2) + pow(y, 2)); }
	inline void absolute() { abs(x); abs(y); }
	inline void operator ()(i32 x, i32 y) { this->x = x; this->y = y; }
	inline void operator ()(const Vec2& vector2d) { x = vector2d.x; y = vector2d.y; }
	inline void operator =(const Vec2& vector2d) { x = vector2d.x; y = vector2d.y; }
	inline Vec2 operator +(const Vec2& other) const { return { x + other.x, y + other.y }; }
	inline Vec2 operator -(const Vec2& other) const { return { x - other.x, y - other.y }; }
	inline Vec2 operator *(const Vec2& other) const { return { x * other.x, y * other.y }; }
	inline Vec2 operator /(const Vec2& other) const { return { x / other.x, y / other.y }; }
	inline Vec2 operator --() { return { x - 1, y - 1 }; }
	inline Vec2 operator ++() { return { x + 1, y + 1 }; }
	inline bool operator ==(const Vec2& other) const { return (x == other.x && y == other.y) ? true : false; }
	inline bool operator !=(const Vec2& other) const { return (x != other.x && y != other.y) ? true : false; }
	inline bool operator >(Vec2 other) { return (magnitude() > other.magnitude()) ? true : false; }
	inline bool operator >=(Vec2 other) { return (magnitude() >= other.magnitude()) ? true : false; }
	inline bool operator <(Vec2 other) { return (magnitude() < other.magnitude()) ? true : false; }
	inline bool operator <=(Vec2 other) { return (magnitude() <= other.magnitude()) ? true : false; }
	friend std::ostream& operator<<(std::ostream& os, const Vec2& vector2d) {
		os << "X: " << vector2d.x << " Y: " << vector2d.y;
		return os;
	}
};

Vec2 RotateRelativeToOrigin(Vec2 pos, Vec2 origin, float deg) {
	/*___Maybe we want to always ceil() instead of round()___*/

	//Store if x or y of curret pixel is negative
	bool xne, yne;

	//Get distance between origin and pixel -> dist is the pixel's position relative to the origin
	Vec2 dist(pos - origin);

	//Check if dist has negative x or y -> helps us to interpret pos_new better
	if (dist.x < 0)
		xne = true;
	if (dist.y < 0)
		yne = true;
	
	//Make negative numbers positive
	dist.absolute();

	//Pythagoras 
	float hypothenuse = dist.magnitude(); // root(dist.x^2 + dist.y^2) 
	
	//Get the angle of alpha
	float angle = atan((float)dist.y / (float)dist.x) * 180.0 / PI + deg; // -> * 180 / PI arc measure to degrees 
	// -> added the deg as an offset
	
	//Calculate the new position of the pixel
	Vec2 pos_new((int)(cos(angle * PI / 180.0) * hypothenuse + 0.5f),
		(int)(sin(angle * PI / 180.0) * hypothenuse + 0.5f));

	//Make it match our alignments

	//return the new position
	return pos_new + origin;
}

int main()
{
	std::thread t1(Window);
	t1.detach();
	Sleep(100);
	HDC dc = GetDC(hwnd);
	Vec2 pos;
	int i = 0;
	while (true) {
		pos = RotateRelativeToOrigin({ 130,130 }, { 100,100 }, i);
		SetPixelV(dc, 100, 100, RGB(255, 0, 0));
		SetPixelV(dc, pos.x, pos.y, RGB(125, 255, 125));
		Sleep(100);
		i += 1;
	}
	Sleep(1000000000);
}
