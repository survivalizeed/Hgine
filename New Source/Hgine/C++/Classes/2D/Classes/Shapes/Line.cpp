

#include "../Objects.h"

sur::Line::Line(Vec2f start_point, Vec2f end_point, Color color, std::string_view name)
{
	this->start_point = start_point;
	this->end_point = end_point;
	this->color = color;
	this->position(0, 0);
	this->type = Type::Line;
	this->name = name;
}

void sur::Line::SetStart(Vec2f start_point)
{
	this->start_point = start_point;
}

void sur::Line::SetEnd(Vec2f end_point)
{
	this->end_point = end_point;
}

sur::Vec2f sur::Line::GetStart()
{
	return start_point;
}

sur::Vec2f sur::Line::GetEnd()
{
	return end_point;
}

void sur::Line::Bind(bool render)
{
	if(render)
		algorithm::DrawLine(start_point + position, end_point + position, color, nullptr, nullptr);
}