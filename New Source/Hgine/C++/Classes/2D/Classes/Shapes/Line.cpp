

#include "../Objects.h"

sur::Line::Line(Vec2f start_point, Vec2f end_point, Color color, std::string_view name)
{
	this->start_point = start_point;
	this->end_point = end_point;
	this->color = color;
	this->position(0, 0);
	this->type = Type::Line;
	this->name = name;
	this->hash = static_cast<i32>(std::hash<std::string>{}(name.data()));
}

void sur::Line::Bind(bool render)
{
	if(render)
		algorithm::DrawLine(start_point + position, end_point + position, color, nullptr, nullptr);
}