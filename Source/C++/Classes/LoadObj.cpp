

#include "Classes.h"

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
	}
	else if (_debug) {
		std::string errstr = "Object path not found!\nPath given: ";
		errstr += path;
		errstr += "\nObject name: ";
		errstr += typeid(this).name();
		l(errstr);
	}
}

sur::Object::Object(const std::string& path, sur::Vec2 position, const std::string& name, i32 id, cb_ptr<Master*> callback)
	: path(path), Master(name, id, position,callback)
{
	type = Type::Object;
	identitys.push_back(id);
	ptrs.push_back(this);
	Load();
}

sur::Object::Object(const Object* const obj, sur::Vec2 position, const std::string& name, i32 id, cb_ptr<Master*> callback)
	: XCoords(obj->XCoords), YCoords(obj->YCoords), Colors(obj->Colors), Master(name,id,position, callback)
{
	type = Type::Object;
	size = obj->size;
	identitys.push_back(id);
	ptrs.push_back(this);
}

void sur::Object::Bind(bool Render, bool Collider, ColliderType collidertype)
{

	if ((position.x < 0 && position.x + size.x < 0) && (position.y < 0 && position.y + size.y < 0)
		|| (position.x > _window_size.x && position.x + size.x > _window_size.x) && (position.y > _window_size.y
			&& position.y + size.y > _window_size.y))
		return;
	if (collidertype == ColliderType::None && Render) {
		for (i32 i = 0; i < YCoords->size(); i++) {
				_Amap.Render(XCoords->at(i) + position.x, YCoords->at(i) + position.y, Colors->at(i).ToCOLORREF());
		}
	}
	if (collidertype == ColliderType::Static) {
		for (i32 i = 0; i < YCoords->size(); i++) {
				if (_debug)
					_Amap.Render(XCoords->at(i) + position.x, YCoords->at(i) + position.y, Color(255, 255, 255));
				else if (Render)
					_Amap.Render(XCoords->at(i) + position.x, YCoords->at(i) + position.y, Colors->at(i).ToCOLORREF());
			if (Collider)
				_Amap.Collider(XCoords->at(i) - CO + position.x, YCoords->at(i) - CO + position.y, id);
		}
		return;
	}
	if (collidertype == ColliderType::Outline) {	// Outlined Collider -> Good for Objects form outside.
		if(Render)
			for (i32 i = 0; i < YCoords->size(); i++)
					_Amap.Render(XCoords->at(i) + position.x, YCoords->at(i) + position.y, Colors->at(i).ToCOLORREF());
		if (Collider) {
			for (i32 i = position.x; i < size.x + position.x; i++) {
				if (_debug)
					_Amap.Render(i, position.y, Color(255, 255, 255));
				_Amap.Collider(i - CO, position.y - CO, id);
			}
			for (i32 i = position.y; i < size.y + position.y; i++) {
				if (_debug)
					_Amap.Render(position.x, i, Color(255, 255, 255));
				_Amap.Collider(position.x - CO, i - CO, id);
			}
			for (i32 i = position.x; i < size.x + position.x; i++) {
				if (_debug)
					_Amap.Render(i, size.y + position.y, Color(255, 255, 255));
				_Amap.Collider(i - CO, size.y - CO + position.y, id);
			}
			for (i32 i = position.y; i < size.y + position.y; i++) {
				if (_debug)
					_Amap.Render(size.x + position.x, i, Color(255, 255, 255));
				_Amap.Collider(size.x - CO + position.x, i - CO, id);
			}
		}
		return;
	}
	if (collidertype == ColliderType::Filled) {
		if(Render)
			for (i32 i = 0; i < YCoords->size(); i++)
					_Amap.Render(XCoords->at(i) + position.x, YCoords->at(i) + position.y, Colors->at(i).ToCOLORREF());
		if(Collider)
			for (i32 a = position.y; a < position.y + size.y; a++)
				for (i32 b = position.x; b < position.x + size.x; b++)
					if (_debug)
						_Amap.Render(b, a, Color(255, 255, 255));
					else
						_Amap.Collider(b - CO, a - CO, id);
		return;
	}
}


void sur::Object::Rotate(sur::Vec2 origin, i32 Angle)
{ 
	//assert(rotatecpy && previous_angle == Angle);
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
	sur::Vec2 v;
	for (i32 i = 0; i < YCoords->size(); ++i) {
		v = rot({XCoords->at(i) + position.x, YCoords->at(i) + position.y }, origin, Angle);
		v = v - position;
		XCoords->at(i) = v.x;
		YCoords->at(i) = v.y;
	}
}



//auto arot = [&](sur::Vec2 pos, sur::Vec2 origin, i32 Angle) -> sur::Vec2 {
//	Angle *= PI / 180;
//	sur::Vec2 pos_new;
//	f32 angle;
//	sur::Vec2 dist(pos - origin);
//	f32 hypothenuse = dist.magnitude();
//	angle = atan((f32)dist.y / (f32)dist.x) + Angle;
//	pos_new((i32)(cos(angle) * hypothenuse + 0.5f),
//		(i32)(sin(angle) * hypothenuse + 0.5f));
//	return pos_new + origin;
//};
//if (xb && yb) {
//	angle = atan((f32)dist.x / (f32)dist.y) + Angle + PI / 2;
//	pos_new((i32)(cos(angle) * hypothenuse + 0.5f),
//		(i32)(sin(angle) * hypothenuse + 0.5f));
//}
//if (xb && !yb) {
//	angle = atan((f32)dist.y / (f32)dist.x) + Angle + PI;
//	pos_new((i32)(sin(angle) * hypothenuse + 0.5f),
//		(i32)(cos(angle) * hypothenuse + 0.5f));
//}
//if (!xb && yb) {
//	angle = atan((f32)dist.x / (f32)dist.y) + Angle + 3 * PI / 2;
//	pos_new((i32)(sin(angle) * hypothenuse + 0.5f),
//		(i32)(cos(angle) * hypothenuse + 0.5f));
//}