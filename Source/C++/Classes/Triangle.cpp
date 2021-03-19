

#include "Classes.h"

extern sur::Map_Analyses _Amap;
extern std::vector<int> identitys;
extern std::vector<void*> ptrs;

void sur::Triangle::LineVector::clear()
{
	memset(check, false, 3);
	Line1->clear();
	Line2->clear();
	Line3->clear();
}

std::vector<sur::Vec2>* sur::Triangle::LineVector::get(int i)
{
	switch (i)
	{
	case 1:
		check[0] = true;
		return this->Line1;
	case 2:
		check[1] = true;
		return this->Line2;
	case 3:
		check[2] = true;
		return this->Line3;
	default:
		return nullptr;
	}
}

std::vector<sur::Vec2>* sur::Triangle::LineVector::getother()
{
	if (!check[0]) {
		check[0] = true;
		return this->Line1;
	}
	if (!check[1]) {
		check[1] = true;
		return this->Line2;
	}
	if (!check[2]) {
		check[2] = true;
		return this->Line3;
	}
	return nullptr;
}

void sur::Triangle::Line(sur::Vec2 start, sur::Vec2 end, std::vector<sur::Vec2>* line, bool Collider)
{
	if (start.x == end.x)
		start.x--;
	int lcounter = 0;
	if (start.y > end.y && start.x > end.x) {
		std::swap(start.y, end.y);
		std::swap(start.x, end.x);
	}
	int Dx, Dy;
	float RunsThrough;
	Dx = end.x - start.x;
	Dy = end.y - start.y;
	RunsThrough = (float)Dy / (float)Dx;
	line->push_back(start);
	if (RunsThrough >= 0) {
		int tempy = start.y;
		float counter = 0.0f;
		int countcounter = 1;
		for (int i = start.x; i <= end.x; i++) {
			if (Collider)
				_Amap.Collider(i, tempy, id);
			_Amap.Render(i, tempy, color.ToCOLORREF());
			while (counter >= countcounter) {
				tempy++;
				line->push_back({ i,tempy });
				if (Collider)
					_Amap.Collider(i, tempy, id);
				_Amap.Render(i, tempy, color.ToCOLORREF());
				countcounter++;
			}
			counter += RunsThrough;
		}
	}
	else {
		RunsThrough *= -1;
		int tempy = start.y;
		float counter = 0.0f;
		int countcounter = 1;
		bool runned = false;
		for (int i = start.x; i <= end.x; i++) {
			if (Collider)
				_Amap.Collider(i, tempy, id);
			_Amap.Render(i, tempy, color.ToCOLORREF());
			while (counter >= countcounter) {
				tempy--;
				line->push_back({ i,tempy });
				if (Collider)
					_Amap.Collider(i, tempy, id);
				_Amap.Render(i, tempy, color.ToCOLORREF());
				countcounter++;
			}
			runned = true;
			counter += RunsThrough;
		}
		if (!runned) {
			RunsThrough = (float)Dx / (float)Dy;
			RunsThrough *= -1;
			int tempx = start.x;
			for (int i = start.y; i <= end.y; i++) {
				line->push_back({ tempx,i });
				if (Collider)
					_Amap.Collider(tempx, i, id);
				_Amap.Render(tempx, i, color.ToCOLORREF());
				while (counter >= countcounter) {
					tempx--;
					if (Collider)
						_Amap.Collider(tempx, i, id);
					_Amap.Render(tempx, i, color.ToCOLORREF());
					countcounter++;
				}
				counter += RunsThrough;
			}
		}
	}
}

auto max_val = [](int a, int b, int c) {
	if (a >= b && a >= c)
		return 1;
	if (b >= a && b >= c)
		return 2;
	if (c >= a && c >= b)
		return 3;
	return 0;
};

auto min_val = [](int a, int b) { return a <= b ? 1 : 2; };

auto near_comp = [](int target, int a, int b) { return (abs(target - a) < abs(target - b)) ? 1 : 2; };

void sur::Triangle::Fill(LineVector& linevector)
{

	int maxv = max_val((int)linevector.Line1->size(), (int)linevector.Line2->size(), (int)linevector.Line3->size());
	std::vector<sur::Vec2>* hypo = nullptr;
	std::vector<sur::Vec2>* other = nullptr;
	std::vector<sur::Vec2>* temp = nullptr;
	
	hypo = linevector.get(maxv);
	other = linevector.getother();
	temp = linevector.getother();
	
	if (hypo->at(0).y > hypo->at(hypo->size() - 1).y)
		std::reverse(hypo->begin(), hypo->end());
	if (other->at(0).y > other->at(other->size() - 1).y)
		std::reverse(other->begin(), other->end());
	if (temp->at(0).y > temp->at(temp->size() - 1).y)
		std::reverse(temp->begin(), temp->end());

	int dir = 0;
	if (near_comp(hypo->at(0).y, other->at(0).y, temp->at(0).y) == 1) {
		other->insert(other->end(), temp->begin(), temp->end());	//Ersetzen mit else unten
		dir = min_val(hypo->at(hypo->size() / 2).x, other->at(other->size() / 2).x);
		int counter = 0;
		for (int i = hypo->at(0).y; i < hypo->at(hypo->size() - 1).y; i++) {
			if (dir == 1) {
				if (counter < hypo->size() && counter < other->size())
					for (int j = hypo->at(counter).x; j <= other->at(counter).x; j++)
						_Amap.Render(j, i, color.ToCOLORREF());
			}
			else {
				if (counter < hypo->size() && counter < other->size())
					for (int j = other->at(counter).x; j <= hypo->at(counter).x; j++)
						_Amap.Render(j, i, color.ToCOLORREF());
			}
			counter++;
		}
	}
	else {
		temp->insert(temp->end(), other->begin(), other->end());
		dir = min_val(hypo->at(hypo->size() / 2).x, temp->at(temp->size() / 2).x);
		int counter = 0;
		for (int i = hypo->at(0).y; i < hypo->at(hypo->size() - 1).y; i++) {
			if (dir == 1) {
				if (counter < hypo->size() && counter < temp->size())
					for (int j = hypo->at(counter).x; j <= temp->at(counter).x; j++)
						_Amap.Render(j, i, color.ToCOLORREF());
			}
			else {
				if (counter < hypo->size() && counter < temp->size())
					for (int j = temp->at(counter).x; j <= hypo->at(counter).x; j++)
						_Amap.Render(j, i, color.ToCOLORREF());
			}
			counter++;
		}
	}
}

sur::Triangle::Triangle(sur::Vec2 p1, sur::Vec2 p2, sur::Vec2 p3, Color color, const std::string& name, int id)
	: p1(p1), p2(p2), p3(p3), color(color), Master(name, id) 
{
	identitys.push_back(id);
	ptrs.push_back(this);
}


void sur::Triangle::Bind(bool Collider)
{
	Line(p1, p2, linevector.Line1,Collider);
	Line(p2, p3, linevector.Line2,Collider);
	Line(p3, p1, linevector.Line3,Collider);
	Fill(linevector);
	linevector.clear();
}