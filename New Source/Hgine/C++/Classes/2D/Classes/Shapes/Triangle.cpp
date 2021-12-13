

#include "../Objects.h"

sur::Triangle::Triangle(Vec2f p1, Vec2f p2, Vec2f p3, Color color, std::string_view name)
{
	Vec2f min;
	if (p1.magnitude() <= p2.magnitude() && p1.magnitude() <= p3.magnitude())
		min = p1;
	if (p2.magnitude() <= p1.magnitude() && p2.magnitude() <= p3.magnitude())
		min = p2;
	if (p3.magnitude() <= p1.magnitude() && p3.magnitude() <= p2.magnitude())
		min = p3;
	this->p1 = p1 - min;
	this->p2 = p2 - min;
	this->p3 = p3 - min;
	this->color = color;
	this->position = min;
	this->original_position = position;
	this->type = Type::Triangle;
	this->name = name;
	this->hash = static_cast<i32>(std::hash<std::string>{}(name.data()));
	Manager::Add(this);
	_objects.push_back(this);
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

sur::Vec2f sur::Triangle::GetPoint(u32 index) const
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

void sur::Triangle::Bind()
{
	if (childOfCamera) {
		position = original_position - STA(_camera_offset);
	}
	else {
		original_position = position + STA(_camera_offset);
	}

	DoRelevantChecks();

	if (render) {
		if (renderMode == RenderMode::Wireframe)
			algorithm::DrawTriangleWire(p1 + position, p2 + position, p3 + position, TintPixel(color));
		else
			algorithm::DrawTriangle(p1 + position, p2 + position, p3 + position, TintPixel(color));
	}
	
}

