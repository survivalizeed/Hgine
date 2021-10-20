

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

void sur::GameObject::CheckCollision()
{
	anyCollisionLeft = false;

	for (i32 i = static_cast<i32>(previousCall.size()); i < _gameObjects.size(); ++i) {
		previousCall.push_back(false);
		collided.push_back(false);
	}
	for (i32 i = 0; i < collided.size(); ++i) {
		collided[i] = false;
	}
	for (i32 i = 0; i < _gameObjects.size(); ++i) {
		if (this == _gameObjects[i] || _gameObjects[i]->collider != Collider::AABB)
			continue;
		if (algorithm::AABB(GetSquareOrSpriteStart(*this) - STA({ 1,1 }), GetSquareOrSpriteEnd(*this) + STA({ 1,1 }),
			GetSquareOrSpriteStart(*_gameObjects[i]), GetSquareOrSpriteEnd(*_gameObjects[i]))) {

			if (!previousCall[i]) {
				if (this->onCollisionEnter != nullptr)
					this->onCollisionEnter(this, _gameObjects[i]);
				if (_gameObjects[i]->onCollisionEnter != nullptr)
					_gameObjects[i]->onCollisionEnter(_gameObjects[i], this);
			}
			if (this->onCollisionStay != nullptr)
				this->onCollisionStay(this, _gameObjects[i]);
			if (_gameObjects[i]->onCollisionStay != nullptr)
				_gameObjects[i]->onCollisionStay(_gameObjects[i], this);
			collided[i] = true;
			anyCollisionLeft = true;
		}
	}
	for (i32 i = 0; i < collided.size(); ++i)
		if (collided[i])
			previousCall[i] = true;

	for (i32 i = 0; i < collided.size(); ++i) {
		if (!collided[i] && previousCall[i]) {
			if (this->onCollisionExit != nullptr)
				this->onCollisionExit(this, _gameObjects[i]);
			if (_gameObjects[i]->onCollisionExit != nullptr)
				_gameObjects[i]->onCollisionExit(_gameObjects[i], this);

			previousCall[i] = false;
		}
	}

}

void sur::GameObject::AABBmove(sur::GameObject* current, Vec2 incomingDirection) {

	auto MakeAABB = [=](sur::GameObject* first, sur::GameObject* second) -> bool
	{
		Vec2f fsta = GetSquareOrSpriteStart(*first);
		Vec2f fend = GetSquareOrSpriteEnd(*first);

		Vec2f ssta = GetSquareOrSpriteStart(*second);
		Vec2f send = GetSquareOrSpriteEnd(*second);
		return algorithm::AABB(fsta, fend, ssta, send);
	};

	bool alreadyDecreased = false;
	for (i32 i = 0; i < _gameObjects.size(); ++i) {
		if (this == _gameObjects[i] || _gameObjects[i]->collider != Collider::AABB)
			continue;
		this->position += STA(incomingDirection);
		while (MakeAABB(this, _gameObjects[i])) {
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

sur::Vec2 sur::GameObject::Move(Vec2f direction, i32 moveQueueIndex)
{
	Vec2 move = MoveQueue(direction, moveQueueIndex);
	if (move.x == 0 && move.y == 0) return { 0, 0 };
	if (this->collider == Collider::AABB)
		AABBmove(this, move);
	if(this->collider == Collider::None)
		this->position += STA(move);
	return move;
}
