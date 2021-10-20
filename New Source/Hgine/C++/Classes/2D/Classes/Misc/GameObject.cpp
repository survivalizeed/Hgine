

#include "../Objects.h"

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
			}

			if (this->onCollisionStay != nullptr)
				this->onCollisionStay(this, _gameObjects[i]);
			collided[i] = true;
			anyCollisionLeft = true;
		}
	}
	for (i32 i = 0; i < collided.size(); ++i)
		if (collided[i] && this != _gameObjects[i])
			previousCall[i] = true;

	for (i32 i = 0; i < collided.size(); ++i) {
		if (!collided[i] && previousCall[i] && this != _gameObjects[i]) {
			if (this->onCollisionExit != nullptr)
				this->onCollisionExit(this, _gameObjects[i]);
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
	if (this->collider == Collider::None)
		this->position += STA(move);
	return move;
}