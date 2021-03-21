

#include "Classes.h"

extern sur::Map_Analyses _Amap;
extern std::vector<int> identitys;
extern std::vector<void*> ptrs;


void sur::LoadObj::Load()
{

	std::string Data = "";
	std::string Nums = "0123456789";
	std::string ColorRef = "";
	std::ifstream file(Path);
	if (file) {
		std::ostringstream ss;
		ss << file.rdbuf();
		Data = ss.str();
		file.close();

		int count;
		for (int i = 0; i < Data.size(); i++) {
			if (Data[i] == '-') {
				x++;
			}
			if (Data[i] == 'E') {
				y++;
				MaxX->push_back(x);
				x = 0;
			}
			if (Data[i] == '/') {
				for (int j = 1;; j++) {
					count = 0;
					for (int a = 0; a < Nums.size(); a++) {
						if (Data[i + j] == Nums[a]) {
							ColorRef += Data[i + j];
							count++;
						}
						else if (a == Nums.size() - 1 && count == 0) {
							goto Leave;
						}
					}
				}
			Leave:
				XCoords->push_back(x);
				YCoords->push_back(y);
				Colors->push_back(std::stoi(ColorRef));
				x++;
				ColorRef = "";
			}
		}
		size.x = *std::max_element(MaxX->begin(), MaxX->end());
		size.y = y;
		delete MaxX;
	}
	else if (_debug) {
		std::string errstr = "Object path not found!\nPath given: ";
		errstr += Path;
		errstr += "\nObject name: ";
		errstr += typeid(this).name();
		l(errstr);
	}
}

sur::LoadObj::LoadObj(const char* Path, sur::Vec2 position, const std::string& name, int id)
	: Path(Path), Master(name, id, position)
{
	identitys.push_back(id);
	ptrs.push_back(this);
	Load();
}

void sur::LoadObj::MoveInject(int index, int CurMove)	//Def in Master <- No override needed???
{

	switch (index)
	{
	case 1:
		position.y -= CurMove;
		break;
	case 2:
		position.x += CurMove;
		break;
	case 3:
		position.y += CurMove;
		break;
	case 4:
		position.x -= CurMove;
		break;
	}

}

void sur::LoadObj::Bind(bool Collider, ColliderType collidertype)
{

	if ((position.x < 0 && position.x + size.x < 0) || (position.y < 0 && position.y + size.y < 0)
		|| (position.x > _window_size.x && position.x + size.x > _window_size.x) || (position.y > _window_size.y
			&& position.y + size.y > _window_size.y))
		return;
	if (collidertype == ColliderType::Static) {
		for (int i = 0; i < YCoords->size(); i++) {
				if (_debug)
					_Amap.Render(XCoords->at(i) + position.x, YCoords->at(i) + position.y, Color(255, 255, 255));
				else
					_Amap.Render(XCoords->at(i) + position.x, YCoords->at(i) + position.y, Colors->at(i).ToCOLORREF());
			if (Collider)
				_Amap.Collider(XCoords->at(i) - CO + position.x, YCoords->at(i) - CO + position.y, id);
		}
		return;
	}
	if (collidertype == ColliderType::Outline) {	// Outlined Collider -> Good for Objects form outside.
		for (int i = 0; i < YCoords->size(); i++)
				_Amap.Render(XCoords->at(i) + position.x, YCoords->at(i) + position.y, Colors->at(i).ToCOLORREF());
		for (int i = position.x; i < size.x + position.x; i++)
			if (Collider) {
				if (_debug)
					_Amap.Render(i, position.y, Color(255, 255, 255));
				_Amap.Collider(i - CO, position.y - CO, id);
			}
		for (int i = position.y; i < size.y + position.y; i++)
			if (Collider) {
				if (_debug)
					_Amap.Render(position.x, i, Color(255, 255, 255));
				_Amap.Collider(position.x - CO, i - CO, id);
			}
		for (int i = position.x; i < size.x + position.x; i++)
			if (Collider) {
				if (_debug)
					_Amap.Render(i, size.y + position.y, Color(255, 255, 255));
				_Amap.Collider(i - CO, size.y - CO + position.y, id);
			}
		for (int i = position.y; i < size.y + position.y; i++)
			if (Collider) {
				if (_debug)
					_Amap.Render(size.x + position.x, i, Color(255, 255, 255));
				_Amap.Collider(size.x - CO + position.x, i - CO, id);
			}
		return;
	}
	if (collidertype == ColliderType::Filled) {
		for (int i = 0; i < YCoords->size(); i++)
				_Amap.Render(XCoords->at(i) + position.x, YCoords->at(i) + position.y, Colors->at(i).ToCOLORREF());
		for (int a = position.y; a < position.y + size.y; a++)
			for (int b = position.x; b < position.x + size.x; b++)
				if (Collider) {
					if (_debug)
						_Amap.Render(b, a, Color(255, 255, 255));
					_Amap.Collider(b - CO, a - CO, id);
				}
		return;
	}
}

