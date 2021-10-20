

#include "../Objects.h"

sur::Square::Square(Vec2f start_point, Vec2f end_point, Color color, Collider collider, std::string_view name)
{
	this->start_point = start_point;
	this->end_point = end_point;
	this->color = color;
	this->position(0, 0);
	this->type = Type::Square;
	this->collider = collider;
	this->name = name;
	this->hash = static_cast<i32>(std::hash<std::string>{}(name.data()));
	_gameObjects.push_back(this);
}

void sur::Square::Bind(bool render)
{
	Vec2 local_start_point = ATS(start_point);
	Vec2 local_end_point = ATS(end_point);

	if(collider != Collider::None)
		CheckCollision();

	if (render) {
		for (i32 i = local_start_point.y; i <= local_end_point.y; ++i) {
			for (i32 j = local_start_point.x; j <= local_end_point.x; ++j) {
				Set(Vec2(j, i) + ATS(position), color);
			}
		}
	}
}