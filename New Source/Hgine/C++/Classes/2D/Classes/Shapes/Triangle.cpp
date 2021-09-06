

#include "../Objects.h"

sur::Triangle::Triangle(Vec2f p1, Vec2f p2, Vec2f p3, Color color, std::string_view name)
{
	this->p1 = p1;
	this->p2 = p2;
	this->p3 = p3;
	this->color = color;
	this->position(0, 0);
	this->type = Type::Triangle;
	this->name = name;
}

void sur::Triangle::SetPoint(u32 index, Vec2f position)
{
	if (index == 0)
		p1 = position;
	else if (index == 1)
		p2 = position;
	else if (index == 2)
		p3 = position;
	else {
#ifdef _DEBUG
		Error("Triangle SetPoint(...) index out of range. Meant to be between 0 and 2.");
#endif
	}
}

sur::Vec2f sur::Triangle::GetPoint(u32 index)
{
	if (index == 0)
		return p1;
	else if (index == 1)
		return p2;
	else if (index == 2)
		return p3;
	else {
#ifdef _DEBUG
		Error("Triangle GetPoint(...) index out of range. Meant to be between 0 and 2.");
#endif
		return { 0.f, 0.f };
	}
}

void sur::Triangle::Bind(bool render, bool wireframe)
{
	if (render)
		if (wireframe)
			algorithm::DrawTriangleWire(p1 + position, p2 + position, p3 + position, color);
		else
			algorithm::DrawTriangle(p1 + position, p2 + position, p3 + position, color);
	
}

