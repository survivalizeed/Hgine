

#include "Hgine/Includes.h"

using namespace sur;

void ToSquare(std::array<std::string, 15>& virtual_field, Square(&field)[15][15]) {
	
	//std::reverse(virtual_field.begin(), virtual_field.end());
	
	for (i32 y = 0; y < 15; ++y) {
		for (i32 x = 0; x < 15; ++x) {
			if (virtual_field[x][y] == 'X')
				field[x][y] = Square(
					{ static_cast<f32>(50 * x), static_cast<f32>(50 * (15 - y - 1)) },
					{ static_cast<f32>(50 * (x + 1)), static_cast<f32>(50 * (15 - y)) },
					Color(255, 0, 0), "X");
			if (virtual_field[x][y] == ' ')
				field[x][y] = Square(
					{ static_cast<f32>(50 * x), static_cast<f32>(50 * (15 - y - 1)) },
					{ static_cast<f32>(50 * (x + 1)), static_cast<f32>(50 * (15 - y)) },
					Color(100, 100, 100), " ");
			if (virtual_field[x][y] == 'A')
				field[x][y] = Square(
					{ static_cast<f32>(50 * x), static_cast<f32>(50 * (15 - y - 1)) },
					{ static_cast<f32>(50 * (x + 1)), static_cast<f32>(50 * (15 - y)) },
					Color(0, 255, 0), " ");
			if (virtual_field[x][y] == 'P')
				field[x][y] = Square(
					{ static_cast<f32>(50 * x), static_cast<f32>(50 * (15 - y - 1)) },
					{ static_cast<f32>(50 * (x + 1)), static_cast<f32>(50 * (15 - y)) },
					Color(0, 255, 255), " ");
		}
	}
}


void Clear(std::array<std::string, 15>& virtual_field) {
	virtual_field =
	{
		"XXXXXXXXXXXXXXX",
		"X             X",
		"X             X",
		"X             X",
		"X             X",
		"X             X",
		"X             X",
		"X             X",
		"X             X",
		"X             X",
		"X             X",
		"X             X",
		"X             X",
		"X             X",
		"XXXXXXXXXXXXXXX",
	};
}

int main() {

	wndInitialize(Vec2(750, 750), Vec2(750, 750), "", "");
	wndCreate("Hgine Demo", WS_OVERLAPPEDWINDOW);

	Renderer renderer(Color(0, 0, 0), false, 0.f, false);
	renderer.FPS();

	Square field [15][15];

	Keys latestInput = None;

	Vec2 playerPos = { 5, 5 };

	Vec2 apple(sur::RandomRange(1, 13), sur::RandomRange(1, 13));

	std::array<std::string, 15> virtual_field;

	std::vector<Vec2> snake;


	snake.push_back(playerPos);

	bool found = false;
	bool dead = false;
	bool nextrun = false;

	i32 score = 0;
	i32 gameSpeed = 50;


	for (;;) {
		renderer.Clear();
		
		Clear(virtual_field);

		virtual_field[apple.x][apple.y] = 'A';
		
		{
			std::vector<Vec2> snakeTMP(snake);
			for (i32 i = 1; i < snake.size(); ++i) {
				snake[i] = snakeTMP[(size_t)i - 1];
			}
		}

		snake[0] = playerPos;

		if (virtual_field[playerPos.x][playerPos.y] == 'A') {
			found = true;
			apple(sur::RandomRange(1, 13), sur::RandomRange(1, 13));
			++score;

		}
		else if (virtual_field[playerPos.x][playerPos.y] == 'X' || virtual_field[playerPos.x][playerPos.y] == 'P') {
			MessageBoxA(_window_hwnd, "You died", "Game", MB_SERVICE_NOTIFICATION_NT3X);
			return 0;
		}


		for (i32 i = 0; i < snake.size(); ++i) {
			virtual_field[snake[i].x][snake[i].y] = 'P';
		}

		if (found) {
			switch (latestInput) {
			case W:
				snake.push_back({ snake[snake.size() - 1].x, snake[snake.size() - 1].y + 1 });
				break;
			case A:
				snake.push_back({ snake[snake.size() - 1].x + 1, snake[snake.size() - 1].y});
				break;
			case S:
				snake.push_back({ snake[snake.size() - 1].x, snake[snake.size() - 1].y - 1});
				break;
			case D:
				snake.push_back({ snake[snake.size() - 1].x - 1, snake[snake.size() - 1].y});
				break;
			}
			found = false;
		}
		
		for (i32 i = 0; i < 1000; ++i) {
			if (Input::Keyboard::KeyHeld(W)) latestInput = W;
			else if (Input::Keyboard::KeyHeld(A)) latestInput = A;
			else if (Input::Keyboard::KeyHeld(S))  latestInput = S;
			else if (Input::Keyboard::KeyHeld(D)) latestInput = D;
		}

		switch (latestInput) {
		case W: playerPos.y--; break;
		case A: playerPos.x--; break;
		case S: playerPos.y++; break;
		case D: playerPos.x++; break;
		}


		ToSquare(virtual_field, field);
		for (i32 y = 0; y < 15; ++y) {
			for (i32 x = 0; x < 15; ++x) {
				field[x][y].Bind(true);
			}
		}
		renderer.Render();
		Sleep(100);
	}
}
