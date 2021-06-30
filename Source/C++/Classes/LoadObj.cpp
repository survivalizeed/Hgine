

#include "Classes.h"
#include "../Functional/functional.h"

extern sur::Map_Analyses _Amap;
extern std::vector<i32> identitys;
extern std::vector<void*> ptrs;
extern std::vector<sur::Light*> lights;

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
		for (i32 i = 0; i < Colors->size(); ++i) {
			sRGB tmp(GetRValue(Colors->at(i)), GetGValue(Colors->at(i)), GetBValue(Colors->at(i)));
			Colors->at(i) = Color(tmp.r, tmp.g, tmp.b);
		}	
		i32 maxY = *std::max_element(YCoords->begin(), YCoords->end());
		for (auto&& iter : *YCoords) {
			iter = maxY - iter;
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


sur::Object::Object(const std::string& path, Vec2f position, const std::string& name, i32 id, const std::vector<int>& ignoreids,
	const std::vector<i32>& push, cb_ptr<Master*> callback)
	: path(path), Master(name, id, position,callback)
{
	this->push = push;
	parentmem = false;
	ignore = ignoreids;
	type = Type::Object;
	identitys.push_back(id);
	ptrs.push_back(this);
	Load();
}

sur::Object::Object(const Object* const obj, Vec2f position, const std::string& name, i32 id, const std::vector<int>& ignoreids,
	const std::vector<i32>& push,cb_ptr<Master*> callback)
	: XCoords(obj->XCoords), YCoords(obj->YCoords), Colors(obj->Colors), Master(name,id,position, callback)
{
	this->push = push;
	parentmem = true;
	ignore = ignoreids;
	type = Type::Object;
	size = obj->size;
	identitys.push_back(id);
	ptrs.push_back(this);
}

sur::Vec2 Rotate(sur::Vec2 vec, sur::Vec2 origin, i32 angle) {
	if (angle == 0) return vec;
	sur::Vec2 tmpv(origin - vec);
	angle += 180;
	sur::Mat2x2 tmpm
	(
		cos(angle * PI / 180), -sin(angle * PI / 180),
		sin(angle * PI / 180), cos(angle * PI / 180)
	);
	sur::Vec2 a(tmpm.multiplyWithVector(tmpv) + origin);
	return a;
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
	auto LightIt = [=](Vec2 pos, Color color) -> Color
	{
		bool distTooFar = false;
		bool runned = false;
		bool allow = true;
		sRGB expected(0,0,0);
		sRGB colorRGB(0,0,0);
		colorRGB.ToRGB(color);
		for (auto& iter : lights) {
			runned = true;
			f32 maxDist = iter->radius;
			
			expected.ToRGB(iter->color);

			Vec2f middle(iter->GetPosition());
			f32 dist = sur::Absolute(STA(pos) - middle).magnitude();
			
			if (dist > maxDist) {
				if(allow)
					distTooFar = true;
				continue;
			}
			distTooFar = false;
			allow = false;
			colorRGB = colorRGB + (sRGB(expected.r / (dist * 0.17f), expected.g / (dist * 0.17f), expected.b / (dist * 0.17f)));

			if (colorRGB.r > 255) colorRGB.r = 255;
			if (colorRGB.r < 0) colorRGB.r = 0;
			if (colorRGB.g > 255) colorRGB.g = 255;
			if (colorRGB.g < 0) colorRGB.g = 0;
			if (colorRGB.b > 255) colorRGB.b = 255;
			if (colorRGB.b < 0) colorRGB.b = 0;	

			//i32 maxminimal;
			//if (colorRGB.r <= colorRGB.g && colorRGB.r <= colorRGB.b)
			//	maxminimal = colorRGB.r;
			//if (colorRGB.g <= colorRGB.r && colorRGB.g <= colorRGB.b)
			//	maxminimal = colorRGB.g;
			//if (colorRGB.b <= colorRGB.r && colorRGB.b <= colorRGB.g)
			//	maxminimal = colorRGB.b;	
			//colorRGB = sRGB(colorRGB.r - maxminimal, colorRGB.g - maxminimal, colorRGB.b - maxminimal);
		}
		if (!runned || distTooFar)
			return Color(0, 0, 0);
		return  Color(colorRGB.r, colorRGB.g, colorRGB.b);
	};

	if (OutOfScreenCheck()) return; //Don't use this for matrix edited objects

	CollisionPos.clear();

	if (collidertype == ColliderType::None && Render) {
		for (i32 i = 0; i < YCoords->size(); i++) {
			_Amap.Render(Rotate(matrix.multiplyWithVector(Vec2(XCoords->at(i), YCoords->at(i))) + position, ATS(origin), angle),
				LightIt({ XCoords->at(i), YCoords->at(i) }, TintIt(Colors->at(i)))
			);
		}
	}
	if (collidertype == ColliderType::Static) {
		for (i32 i = 0; i < YCoords->size(); i++) {
			if (Render)
				if(_debug)
					_Amap.Render(Rotate(matrix.multiplyWithVector(Vec2(XCoords->at(i), YCoords->at(i))) + position, ATS(origin), angle),
						Color(255,0,0));
				else
					_Amap.Render(Rotate(matrix.multiplyWithVector(Vec2(XCoords->at(i), YCoords->at(i))) + position, ATS(origin), angle),
						TintIt(Colors->at(i)));
			_Amap.Collider(Rotate(matrix.multiplyWithVector(Vec2(XCoords->at(i), YCoords->at(i))) + position, ATS(origin), angle),
				id);
		}
		return;
	}
	if (collidertype == ColliderType::Outline) {
		if(Render)
			for (i32 i = 0; i < YCoords->size(); i++)
				_Amap.Render(Rotate(matrix.multiplyWithVector(Vec2(XCoords->at(i), YCoords->at(i))) + position, ATS(origin), angle),
					TintIt(Colors->at(i)));
			for (i32 i = 0; i < size.x; i++) {
				sur::Vec2 tmp(Rotate(matrix.multiplyWithVector(Vec2(i, 0 )) + position, ATS(origin), angle));
				CollisionPos.push_back(tmp);
				if(_debug)
					_Amap.Render(tmp, Color(255,0,0));
				_Amap.Collider(tmp, id);
			}
			for (i32 i = 0; i < size.y; i++) {
				sur::Vec2 tmp(Rotate(matrix.multiplyWithVector(Vec2(0, i )) + position, ATS(origin), angle));
				CollisionPos.push_back(tmp);
				if (_debug)
					_Amap.Render(tmp, Color(255, 0, 0));
				_Amap.Collider(tmp, id);
			}
			for (i32 i = 0; i < size.x; i++) {
				sur::Vec2 tmp(Rotate(matrix.multiplyWithVector(Vec2(i, size.y )) + position, ATS(origin), angle));
				CollisionPos.push_back(tmp);
				if (_debug)
					_Amap.Render(tmp, Color(255, 0, 0));
				_Amap.Collider(tmp, id);
			}
			for (i32 i = 0; i < size.y; i++) {
				sur::Vec2 tmp(Rotate(matrix.multiplyWithVector(Vec2(size.x, i )) + position, ATS(origin), angle));
				CollisionPos.push_back(tmp);
				if (_debug)
					_Amap.Render(tmp, Color(255, 0, 0));
				_Amap.Collider(tmp, id);
			}
		return;
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

void sur::Object::FlipX(bool flip)
{
	if (this->fliped_X != flip) {
		i32 maxX = *std::max_element(XCoords->begin(), XCoords->end());
		for (auto&& iter : *XCoords) {
			iter = maxX - iter;
		}
	}
	this->fliped_X = flip;
}

void sur::Object::FlipY(bool flip)
{
	if (this->fliped_Y != flip) {
		i32 maxY = *std::max_element(YCoords->begin(), YCoords->end());
		for (auto&& iter : *YCoords) {
			iter = maxY - iter;
		}
	}
	this->fliped_Y = flip;
}