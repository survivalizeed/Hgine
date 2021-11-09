

#include "../Objects.h"

sur::Line::Line(Vec2f start_point, Vec2f end_point, Color color, std::string_view name)
{
	this->start_point = { 0.f, 0.f };
	this->end_point = end_point - start_point;
	this->color = color;
	this->position = start_point;
	this->original_position = position;
	this->type = Type::Line;
	this->name = name;
	this->hash = static_cast<i32>(std::hash<std::string>{}(name.data()));
	_objects.push_back(this);
}

void sur::Line::Bind(bool render)
{
	if (childOfCamera) {
		position = original_position - STA(_camera_offset);
	}
	else {
		original_position = position + STA(_camera_offset);
	}

	DoRelevantChecks();

	if (render) {
		algorithm::DrawLine(start_point + position, end_point + position, color, nullptr, nullptr);
	}
}