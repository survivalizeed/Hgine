

#include "Classes.h"
#include "../Functional/functional.h"

extern sur::Map_Analyses _Amap;
extern std::vector<i32> identitys;
extern std::vector<void*> ptrs;


void sur::Object::Load()
{

	std::string Data = "";
	std::string Nums = "0123456789";
	std::string ColorRef = "";
	std::ifstream file(path);
	if (file) {
		std::vector<i32>* MaxX = new std::vector<i32>;
		std::ostringstream ss;
		ss << file.rdbuf();
		Data = ss.str();
		file.close();

		i32 count;
		for (i32 i = 0; i < Data.size(); i++) {
			if (Data[i] == '-') {
				x++;
			}
			if (Data[i] == 'E') {
				//Get X Value. It will be the last of the row. Here are (X,Y) the last of the row.
				y++;
				MaxX->push_back(x);
				x = 0;
			}
			if (Data[i] == '/') {
				for (i32 j = 1;; j++) {
					count = 0;
					for (i32 a = 0; a < Nums.size(); a++) {
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
		for (i32 i = 0; i < Colors->size(); ++i) {
			sRGB tmp(GetRValue(Colors->at(i)), GetGValue(Colors->at(i)), GetBValue(Colors->at(i)));
			Colors->at(i) = Color(tmp.r, tmp.g, tmp.b);
		}	
		i32 maxY = *std::max_element(YCoords->begin(), YCoords->end());
		for (auto&& iter : *YCoords) {
			iter = maxY - iter;
		}
	}
	else if (_debug) {
		std::string errstr = "Object path not found!\nPath given: ";
		errstr += path;
		errstr += "\nObject name: ";
		errstr += typeid(this).name();
		l(errstr);
	}
}

sur::Object::Object(const std::string& path, Vec2 position, const std::string& name, i32 id, const std::vector<int>& ignoreids,
	cb_ptr<Master*> callback)
	: path(path), Master(name, id, position,callback)
{
	parentmem = false;
	ignore = ignoreids;
	type = Type::Object;
	identitys.push_back(id);
	ptrs.push_back(this);
	Load();
}

sur::Object::Object(const Object* const obj, Vec2 position, const std::string& name, i32 id, const std::vector<int>& ignoreids,
	cb_ptr<Master*> callback)
	: XCoords(obj->XCoords), YCoords(obj->YCoords), Colors(obj->Colors), Master(name,id,position, callback)
{
	parentmem = true;
	ignore = ignoreids;
	type = Type::Object;
	size = obj->size;
	identitys.push_back(id);
	ptrs.push_back(this);
}

void sur::Object::Bind(bool Render, ColliderType collidertype)
{
	auto OutOfScreenCheck = [&]() -> bool {
		return (position.x >= _window_size.x || position.y >= _window_size.y || 
			position.x + size.x < 0 || position.y + size.y < 0) ? true : false;
	};
	auto TintIt = [&](Color color) -> Color
	{
		assert(tint_by == sRGB(0,0,0), color);
		sRGB tmp;
		tmp.ToRGB(color);
		tmp = tmp + tint_by;
		if (tmp.r > 255) tmp.r = 255;
		if (tmp.r < 0) tmp.r = 0;
		if (tmp.g > 255) tmp.g = 255;
		if (tmp.g < 0) tmp.g = 0;
		if (tmp.b > 255) tmp.b = 255;
		if (tmp.b < 0) tmp.b = 0;
		Color c = Color(tmp.r, tmp.g, tmp.b);
		return c;
	};

	if (OutOfScreenCheck()) return; //Needs fix

	CollisionPos.clear();

	if (collidertype == ColliderType::None && Render) {
		for (i32 i = 0; i < YCoords->size(); i++) {
			_Amap.Render(matrix.mulitplyWithVector(Vec2(XCoords->at(i), YCoords->at(i))) + position,
					TintIt(Colors->at(i)));
		}
	}
	if (collidertype == ColliderType::Static) {
		for (i32 i = 0; i < YCoords->size(); i++) {
				if (Render)
					_Amap.Render(matrix.mulitplyWithVector(Vec2(XCoords->at(i), YCoords->at(i))) + position,
						TintIt(Colors->at(i)));
				_Amap.Collider(matrix.mulitplyWithVector(Vec2(XCoords->at(i), YCoords->at(i))) + position, id);
		}
		return;
	}
	if (collidertype == ColliderType::Outline) {	// Outlined Collider -> Good for Objects form outside.
		if(Render)
			for (i32 i = 0; i < YCoords->size(); i++)
				_Amap.Render(matrix.mulitplyWithVector(Vec2(XCoords->at(i), YCoords->at(i))) + position,
					TintIt(Colors->at(i)));
			for (i32 i = 0; i < size.x; i++) {
				sur::Vec2 tmp(matrix.mulitplyWithVector(Vec2(i, 0 )) + position);
				CollisionPos.push_back(tmp);
				if(_debug)
					_Amap.Render(tmp, Color(255,0,0));
				_Amap.Collider(tmp, id);
			}
			for (i32 i = 0; i < size.y; i++) {
				sur::Vec2 tmp(matrix.mulitplyWithVector(Vec2(0, i )) + position);
				CollisionPos.push_back(tmp);
				if (_debug)
					_Amap.Render(tmp, Color(255, 0, 0));
				_Amap.Collider(tmp, id);
			}
			for (i32 i = 0; i < size.x; i++) {
				sur::Vec2 tmp(matrix.mulitplyWithVector(Vec2(i, size.y )) + position);
				CollisionPos.push_back(tmp);
				if (_debug)
					_Amap.Render(tmp, Color(255, 0, 0));
				_Amap.Collider(tmp, id);
			}
			for (i32 i = 0; i < size.y; i++) {
				sur::Vec2 tmp(matrix.mulitplyWithVector(Vec2(size.x, i )) + position);
				CollisionPos.push_back(tmp);
				if (_debug)
					_Amap.Render(tmp, Color(255, 0, 0));
				_Amap.Collider(tmp, id);
			}
		return;
	}
	if (collidertype == ColliderType::Filled) {
		if(Render)
			for (i32 i = 0; i < YCoords->size(); i++)
				_Amap.Render(matrix.mulitplyWithVector(Vec2(XCoords->at(i), YCoords->at(i) )) + Vec2(position.x, position.y),
					TintIt(Colors->at(i)));
			for (i32 a = 0; a < size.y; a++)
				for (i32 b = 0; b < size.x; b++)
					_Amap.Collider(matrix.mulitplyWithVector(Vec2(b, a )) + position, id);
		return;
	}
}

void sur::Object::Rotate(Vec2 origin, i32 Angle)
{ 
	assert(rotatecpy && previous_angle == Angle);
	if (!rotatecpy) {
		XCoordsC = new std::vector<i32>(*XCoords);
		YCoordsC = new std::vector<i32>(*YCoords);
		ColorsC = new std::vector<Color>(*Colors);
		XCoords = XCoordsC; YCoords = YCoordsC; Colors = ColorsC;
		rotatecpy = true;
	}
	else {
		XCoordsC->clear();
		YCoordsC->clear();
		ColorsC->clear();
		std::copy(XCoordsO->begin(), XCoordsO->end(), back_inserter(*XCoordsC));
		std::copy(YCoordsO->begin(), YCoordsO->end(), back_inserter(*YCoordsC));
		std::copy(ColorsO->begin(), ColorsO->end(), back_inserter(*ColorsC));
	}
	previous_angle = Angle;
	Vec2 v;
	for (i32 i = 0; i < YCoords->size(); ++i) {
		v = rot({XCoords->at(i) + position.x, YCoords->at(i) + position.y }, origin, Angle);
		v = v - position;
		XCoords->at(i) = v.x;
		YCoords->at(i) = v.y;
	}
}

void sur::Object::LSD()
{
	sRGB inc(0,0,0);
	switch (sur::RandomRange(1, 6))
	{
	case 1: inc(-1, 1, 1); break;
	case 2: inc(1, -1, 1); break;
	case 3: inc(1, 1, -1); break;
	case 4: inc(-1, -1, -1); break;
	case 5: inc(-1, -1, 1); break;
	case 6: inc(1, -1, -1); break;
	}
	for (i32 i = 0; i < Colors->size(); ++i) {
		sRGB tmp;
		tmp.ToRGB(Colors->at(i));
		tmp = tmp + inc;
		Colors->at(i) = Color(tmp.r, tmp.g, tmp.b);
		tmp = inc;
	}

}
