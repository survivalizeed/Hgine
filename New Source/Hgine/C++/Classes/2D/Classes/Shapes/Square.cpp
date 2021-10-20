

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
	_objects.push_back(this);
}

void sur::Square::Bind(bool render)
{
	Vec2 local_start_point = ATS(start_point);
	Vec2 local_end_point = ATS(end_point);

	collided = false;

	for (i32 i = 0; i < _objects.size(); ++i) {
		if (this == _objects[i] || (_objects[i]->GetType() != Type::Square && _objects[i]->GetType() != Type::Sprite)
			|| _objects[i]->collider != Collider::AABB)
			continue;
		if (algorithm::AABB(start_point + position - STA({1,1}), end_point + position + STA({ 1,1 }),
			GetSquareOrSpriteStart(*_objects[i]), GetSquareOrSpriteEnd(*_objects[i]))) {
			
			if (!previousCall) {	// Has to do a check for all objects individual
				if (this->onCollisionEnter != nullptr)
					this->onCollisionEnter(this, _objects[i]);
				if (_objects[i]->onCollisionEnter != nullptr)
					_objects[i]->onCollisionEnter(_objects[i], this);
			}
			if (this->onCollisionStay != nullptr)
				this->onCollisionStay(this, _objects[i]);
			if (_objects[i]->onCollisionStay != nullptr)
				_objects[i]->onCollisionStay(_objects[i], this);
			collided = true;
		}
	}
	if(collided)
		previousCall = true;

	if (!collided && previousCall) {
		if (this->onCollisionExit != nullptr)
			this->onCollisionExit(this, /*_objects[i]*/_objects[0]);
		//if (_objects[i]->onCollisionExit != nullptr)
		//	_objects[i]->onCollisionExit(_objects[i], this);
		previousCall = false;
	}


	if (render) {
		for (i32 i = local_start_point.y; i <= local_end_point.y; ++i) {
			for (i32 j = local_start_point.x; j <= local_end_point.x; ++j) {
				Set(Vec2(j, i) + ATS(position), color);
			}
		}
	}
}