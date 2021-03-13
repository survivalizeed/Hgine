#include <windows.h>
#include <gdiplus.h>
#include <thread>
#include <sstream>
#include <stdlib.h>
#include <conio.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

#define l(x) std::cout << x << "\n"



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
int XDependY;
int YDependX;
int DistX;
int DistY;
float Steigung;
float Ergebnis;

void Shape(HDC hdc, int P1X, int P1Y, int P2X, int P2Y) {
	int p1x = 20;
	int p2x = 60;
	int p3x = 20;
	int p4x = 80;
	int p1y = 30;
	int p2y = 80;
	int p3y;
	int p4y;

	int D13 = p1x - p3x;
	int D24 = p4x - p2x;

	int right = 0;
	int left = 0;

	int countRight = 0;
	int countLeft = 0;
	int HowMuchYLoop = p2y - p1y;

	std::cout << D24 << std::endl << HowMuchYLoop;
	for (int j = p1y; j <= p2y; j++) {	
		for (int i = p1x - left; i <= p2x + right; i++) {		
			SetPixelV(hdc, i, j, RGB(123, 53, 123));
		}
		if (right <= D24) {
			if (countRight == HowMuchYLoop / D24) {			//?
				right++;
				countRight = 0;
			}
		}
		if (left <= D13) {
			if (countLeft == HowMuchYLoop / D24) {			//?
				left++;
				countLeft = 0;
			}
		}
		countRight++;
		countLeft++;
	}
	for (int i = p3x; i <= p4x; i++) {
		SetPixelV(hdc, i, p2y, RGB(123, 53, 123));
	}
	
}

//void LineToLine(HDC dc,int P1x, int P1y, int P2x, int P2y) {
//	int BigX, SmallX, BigY, SmallY;
//	int Distx, Disty;
//	int StartPosY;
//	if (P1x > P2x) {
//		BigX = P1x;
//		SmallX = P2x;
//		Disty = P2y - P1y;
//		BigY = P2y;
//		SmallY = P1y;
//		StartPosY = P2y;
//	}
//	if (P1x < P2x) {
//		BigX = P2x;
//		SmallX = P1x;
//		BigY = P1y;
//		SmallY = P2y;
//		Disty = P1y - P2y;
//		StartPosY = P1y;
//	}
//	//Disty *= -1;
//	Distx = BigX - SmallX;
//
//	SetPixelV(dc, P1x, P1y, RGB(123, 53, 123));
//	SetPixelV(dc, P2x, P2y, RGB(123, 53, 123));
//	
//	for (int i = SmallX; i <= BigX; i++) {
//		SetPixelV(dc, i, StartPosY, RGB(123, 53, 123));
//	}
//
//}

void L(HDC dc,int x1, int y1, int x2, int y2) {
	int Dx, Dy;
	float SYforX;
	int RunsThrough;
	float fracpart;
	for (int i = x1; i <= x2; i++) {
		SetPixelV(dc, i, y1, RGB(123, 53, 123));
	}
	for (int i = y1; i <= y2; i++) {
		SetPixelV(dc, x2, i, RGB(123, 53, 123));
	}
	Dx = x2 - x1;
	Dy = y2 - y1;
	SYforX = (float)Dx / (float)Dy;
	fracpart = modf(SYforX, &fracpart);
	RunsThrough = 1 / fracpart;
	SYforX += 0.5f;
	int tempy = y1;
	int counter = 0;
	float counterf = 0.0f;
	std::cout << fracpart;
	for (int i = x1; i <= x2; i++) {
		SetPixelV(dc, i, tempy, RGB(123, 53, 123));
		if (counter == (int)SYforX) {
			tempy++;
			SetPixelV(dc, i, tempy, RGB(123, 53, 123));
			counter = 0;
		}
		if (counterf >= RunsThrough) {
			tempy++;
			SetPixelV(dc, i, tempy, RGB(123, 53, 123));
			counterf = 0;
		}		
		counter++;
	}

	//std::cout << Dx << "\n" << Dy;
}










struct Vec2 {
	int x, y;
	friend std::ostream& operator<<(std::ostream& os, const Vec2& vec2) {
		os << "X: " << vec2.x << " Y: " << vec2.y;
		return os;
	}
};


struct Triangle {
	Vec2 a, b, c;
	Triangle(Vec2 a, Vec2 b, Vec2 c) : a(a), b(b), c(c) {}
	void operator()(Vec2 a, Vec2 b, Vec2 c) {
		this->a = a;
		this->b = b;
		this->c = c;
	}
};


struct LineVector {
	bool* got = new bool[3];
	LineVector() { memset(got, false, 3); }
	std::vector<Vec2>* Line1 = new std::vector<Vec2>;
	std::vector<Vec2>* Line2 = new std::vector<Vec2>;
	std::vector<Vec2>* Line3 = new std::vector<Vec2>;
	
	void sf() { memset(got, false, 3); }
	std::vector<Vec2>* get(int i) {
		switch (i)
		{
		case 1:
			got[0] = true;
			return this->Line1;
		case 2:
			got[1] = true;
			return this->Line2;
		case 3:
			got[2] = true;
			return this->Line3;
		default:
			break;
		}
	}

	std::vector<Vec2>* getother() {
		if (got[0] == false) {
			got[0] = true;
			return this->Line1;
		}
		if (got[1] == false) {
			got[1] = true;
			return this->Line2;
		}
		if (got[2] == false) {
			got[2] = true;
			return this->Line3;
		}
	}
};


void LF(HDC& dc, int x1, int y1, int x2, int y2, COLORREF color, std::vector<Vec2>* line) {
	if (y1 > y2 && x1 > x2) {
		std::swap(y1, y2);
		std::swap(x1, x2);
	}
	int Dx = x2 - x1;
	int Dy = y2 - y1;
	float RunsThrough = (float)Dy / (float)Dx;
	line->push_back({ x1, y1});
	if (RunsThrough >= 0) {
		int tempy = y1;
		float counter = 0.0f;
		int countcounter = 1;
		for (int i = x1; i <= x2; i++) {
			SetPixelV(dc, i, tempy, color);
			while(counter >= countcounter) {
				tempy++;
				line->push_back({ i,tempy });
				SetPixelV(dc, i, tempy, color);
				countcounter++;
			}
			counter += RunsThrough;	
		}
	}
	else {
		RunsThrough *= -1;
		int tempy = y1;	
		float counter = 0.0f;
		int countcounter = 1;
		bool runned = false;
		for (int i = x1; i <= x2; i++) {
			SetPixelV(dc, i, tempy, color);
			while(counter >= countcounter) {
				tempy--;
				line->push_back({ i,tempy });
				SetPixelV(dc, i, tempy, color);
				countcounter++;
			}
			runned = true;
			counter += RunsThrough;
		}
		if (!runned) {
			RunsThrough = (float)Dx / (float)Dy;
			RunsThrough *= -1;
			int tempx = x1;
			for (int i = y1; i <= y2; i++) {
				line->push_back({ tempx,i });
				SetPixelV(dc, tempx, i, color);
				while (counter >= countcounter) {
					tempx--;
					SetPixelV(dc, tempx, i, color);
					countcounter++;
				}
				counter += RunsThrough;
			}
		}
	}
}

int max_val(int a, int b, int c) {
	if (a >= b && a >= c)
		return 1;
	if (b >= a && b >= c)
		return 2;
	if (c >= a && c >= b)
		return 3;
}

int small_val(int a, int b) {
	return a <= b ? 1 : 2;
}

int near_comp(int target, int a, int b) {
	int tempa, tempb;
	tempa = abs(target - a);
	tempb = abs(target - b);
	return (tempa < tempb) ? 1 : 2;
}

void FillWire(HDC& dc,LineVector& linevector, COLORREF color) {
	int maxv = max_val(linevector.Line1->size(), linevector.Line2->size(), linevector.Line3->size());
	auto* hypo = linevector.get(maxv);
	auto* other = linevector.getother();
	auto* temp = linevector.getother();

	if (hypo->at(0).y > hypo->at(hypo->size() - 1).y) 
		std::reverse(hypo->begin(), hypo->end());
	if (other->at(0).y > other->at(other->size() - 1).y)
		std::reverse(other->begin(), other->end());
	if (temp->at(0).y > temp->at(temp->size() - 1).y) 
		std::reverse(temp->begin(), temp->end());
	
	int dir = 0;
	if (near_comp(hypo->at(0).y, other->at(0).y, temp->at(0).y) == 1) {
		other->insert(other->end(), temp->begin(), temp->end());		
		dir = small_val(hypo->at(hypo->size() / 2).x, other->at(other->size() / 2).x);	
		int counter = 0;
		for (int i = hypo->at(0).y; i < hypo->at(hypo->size() - 1).y; i++) {
			if (dir == 1) {
				if (counter < hypo->size() && counter < other->size()) {
					for (int j = hypo->at(counter).x; j <= other->at(counter).x; j++) {
						SetPixel(dc, j, i, color);
					}
				}
			}
			else {
				if (counter < hypo->size() && counter < other->size()) {
					for (int j = other->at(counter).x; j <= hypo->at(counter).x; j++) {
						SetPixel(dc, j, i, color);
					}
				}
			}
			counter++;
		}
	}
	else {
		temp->insert(temp->end(), other->begin(), other->end());
		dir = small_val(hypo->at(hypo->size() / 2).x, temp->at(temp->size() / 2).x);
		int counter = 0;
		for (int i = hypo->at(0).y; i < hypo->at(hypo->size() - 1).y; i++) {
			if (dir == 1) {
				if (counter < hypo->size() && counter < temp->size()) {
					for (int j = hypo->at(counter).x; j <= temp->at(counter).x; j++) {
						SetPixel(dc, j, i, color);
					}
				}
			}
			else {
				if (counter < hypo->size() && counter < temp->size()) {
					for (int j = temp->at(counter).x; j <= hypo->at(counter).x; j++) {
						SetPixel(dc, j, i, color);
					}
				}
			}
			counter++;
		}
	}
}

void PolyWire(HDC& dc, Triangle triangle, LineVector& linevector, COLORREF color) {
	LF(dc, triangle.a.x, triangle.a.y, triangle.b.x, triangle.b.y, color, linevector.Line1);
	LF(dc, triangle.b.x, triangle.b.y, triangle.c.x, triangle.c.y, color, linevector.Line2);
	LF(dc, triangle.c.x, triangle.c.y, triangle.a.x, triangle.a.y, color, linevector.Line3);
}

int main()
{
	std::thread t1(Window);
	t1.detach();
	Sleep(100);
	HDC dc = GetDC(hwnd);
	Triangle triangle({ 10,10 }, { 100,300 }, { 200,200 });
	LineVector linevector;
	POINT point;
	GetCursorPos(&point);
	ScreenToClient(hwnd, &point);
	int i = 5;
	while (true) {
		triangle({ 120,450 }, { i ,100}, { 57,100});
		//Render
		PolyWire(dc, triangle, linevector, RGB(100, 100, 100));			
		FillWire(dc, linevector, RGB(100,100,100));
		Sleep(2);
		linevector.Line1->clear();
		linevector.Line2->clear();
		linevector.Line3->clear();
		linevector.sf();
		PolyWire(dc, triangle, linevector, RGB(50, 50, 50));
		FillWire(dc, linevector, RGB(50, 50, 50));
		linevector.Line1->clear();
		linevector.Line2->clear();
		linevector.Line3->clear();
		linevector.sf();
		i += 5;
	}
	Sleep(10000000);
}


