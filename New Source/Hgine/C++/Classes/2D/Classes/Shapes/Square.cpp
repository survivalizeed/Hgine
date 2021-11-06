

#include "../Objects.h"

bool sur::Square::CheckOutOfScreen()
{
	Vec2f local_start_point;
	Vec2f local_end_point;
	local_start_point = start_point + position + STA(_camera_offset);
	local_end_point = end_point + position + STA(_camera_offset);
	if ((local_start_point.x < 0 && local_end_point.x < 0) || (local_start_point.y < 0 && local_end_point.y < 0))
		return true;
	if ((local_start_point.x > _window_size.x && local_end_point.x > _window_size.x) ||
		(local_start_point.y > _window_size.y && local_end_point.y > _window_size.y))
		return true;
	return false;
}

sur::Square::Square(Vec2f start_point, Vec2f end_point, Color color, std::string_view name)
{
	this->start_point = start_point;
	this->end_point = end_point;
	this->color = color;
	this->position(0, 0);
	this->original_position = position;
	this->type = Type::Square;
	this->name = name;
	this->hash = static_cast<i32>(std::hash<std::string>{}(name.data()));
	_objects.push_back(this);
}

void sur::Square::Bind(bool render)
{
	if (childOfCamera) {
		position = original_position - STA(_camera_offset);
	}
	else {
		original_position = position + STA(_camera_offset);
	}
	Vec2 local_start_point = ATS(start_point);
	Vec2 local_end_point = ATS(end_point);

	DoRelevantChecks();

	if (render) {
		for (i32 i = local_start_point.y; i <= local_end_point.y; ++i) {
			for (i32 j = local_start_point.x; j <= local_end_point.x; ++j) {
				Set(Vec2(j, i) + ATS(position), color);
			}
		}
	}
}
