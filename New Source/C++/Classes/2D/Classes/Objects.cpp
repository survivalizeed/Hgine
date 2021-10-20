

#include "Objects.h"

sur::Vec2 sur::Object::MoveQueue(Vec2f direction, i32 moveQueueIndex)
{
	auto round = [](f32& n)
	{
		f32 pow_10 = pow(10.0f, (f32)3);
		n = ::round(n * pow_10) / pow_10;
	};
	if (!mvContainer.contains(moveQueueIndex)) {
		mvContainer[moveQueueIndex] = MoveQueueContainer();
	}
	MoveQueueContainer cC = mvContainer[moveQueueIndex];
	if (direction.x > 0) {
		cC.counter_pos.x += direction.x;
		round(cC.counter_pos.x);
	}
	else {
		cC.counter_neg.x += direction.x;
		round(cC.counter_neg.x);
	}
	if (direction.y > 0) {
		cC.counter_pos.y += direction.y;
		round(cC.counter_pos.y);
	}
	else {
		cC.counter_neg.y += direction.y;
		round(cC.counter_neg.y);
	}

	Vec2 newDirection;

	while (cC.counter_pos.x >= static_cast<f32>(cC.counter_counter_pos.x))
	{
		newDirection.x++;
		cC.counter_counter_pos.x++;
	}
	while (cC.counter_pos.y >= static_cast<f32>(cC.counter_counter_pos.y))
	{
		newDirection.y++;
		cC.counter_counter_pos.y++;
	}
	while (cC.counter_neg.x <= static_cast<f32>(cC.counter_counter_neg.x))
	{
		newDirection.x--;
		cC.counter_counter_neg.x--;
	}
	while (cC.counter_neg.y <= static_cast<f32>(cC.counter_counter_neg.y))
	{
		newDirection.y--;
		cC.counter_counter_neg.y--;
	}

	mvContainer[moveQueueIndex] = cC;

	return newDirection;
}

void sur::Object::AABB(sur::Object* current, Vec2 incomingDirection) {

	auto PureAABBalgorithm = [=](sur::Object* first, sur::Object* second) -> bool
	{
		
		Vec2f fsta = GetSquareOrSpriteStart(*first);
		Vec2f fend = GetSquareOrSpriteEnd(*first);

		Vec2f ssta = GetSquareOrSpriteStart(*second);
		Vec2f send = GetSquareOrSpriteEnd(*second);

		return algorithm::AABB(fsta, fend, ssta, send);
	};
	
	bool alreadyDecreased = false;
	for (i32 i = 0; i < _objects.size(); ++i) {
		if (this == _objects[i] || (_objects[i]->type != Type::Square && _objects[i]->type != Type::Sprite)
			|| _objects[i]->collider != Collider::AABB)
			continue;
		this->position += STA(incomingDirection);
		while (PureAABBalgorithm(this, _objects[i])) {
			this->position -= STA(incomingDirection);
			alreadyDecreased = true;
			incomingDirection.closerToZeroByOne();
			if (incomingDirection.isZero())
				break;
		}
		if (!alreadyDecreased)
			this->position -= STA(incomingDirection);
		alreadyDecreased = false;
	}
	position += STA(incomingDirection);
}

sur::Vec2 sur::Object::Move(Vec2f direction, i32 moveQueueIndex)
{
	Vec2 move = MoveQueue(direction, moveQueueIndex);
	if (move.x == 0 && move.y == 0) return { 0, 0 };
	if (this->collider == Collider::AABB) {
		AABB(this, move);
	}
	if (this->collider == Collider::None) {
		this->position += STA(move);
	}
	return move;
}

std::string_view sur::Object::GetName() const
{
	return name;
}

sur::Type sur::Object::GetType() const
{
	return type;
}

sur::i32 sur::Object::GetHash() const
{
	return hash;
}
