

#include "LoadObj.h"

extern sur::Map_Analyses _Amap;

void sur::LoadObj::Load()
{
	std::string Data = "";
	std::string Nums = "0123456789";
	std::string ColorRef = "";
	std::ifstream file(Path);
	if (!file) {
		std::string errstr = "Object path not found; Path given: ";
		errstr += Path;
		errstr += "; Object name -> ";
		errstr += typeid(this).name();	
		Error(errstr.c_str());
	}
	std::ostringstream ss;

	ss << file.rdbuf();
	Data = ss.str();
	file.close();

	int count;
	for (int i = 0; i < Data.size(); i++) {
		if (Data[i] == '-')
			x++;
		if (Data[i] == 'E') {
			y++;
			MaxX->push_back(x);
			x = 0;
		}
		if (Data[i] == '/') {
			for (int j = 1; true; j++) {
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
			XCoords.push_back(x + position.x);
			YCoords.push_back(y + position.y);
			Colors.push_back(std::stoi(ColorRef));
			x++;
			ColorRef = "";
		}
	}
	MaxXvalue = *std::max_element(MaxX->begin(), MaxX->end());
	delete MaxX;
}

void sur::LoadObj::Bind()
{
	for (int i = 0; i < YCoords.size(); i++) {
		_Amap.Render(XCoords[i], YCoords[i], Colors[i].ToCOLORREF());
	}
}

void sur::LoadObj::Move(sur::Vec2 direction)
{
	for (int i = 0; i < YCoords.size(); i++) {
		YCoords[i] -= direction.y;
		XCoords[i] += direction.x;
	}
}
