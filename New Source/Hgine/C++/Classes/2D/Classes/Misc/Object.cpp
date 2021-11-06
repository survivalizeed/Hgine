

#include "../Objects.h"

void sur::Object::DoRelevantChecks() 
{
	if (boxHover != nullptr)
		boxHover->CheckHover();
	if (collider != nullptr)
		collider->CheckCollision();
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

sur::Vec2f sur::Object::GetOriginalPosition() const
{
	return original_position;
}

sur::Vec2 sur::Object::Move(Vec2f direction, i32 moveQueueIndex)
{
	Vec2 move = MoveQueue(direction, moveQueueIndex);
	if (move.x == 0 && move.y == 0) return { 0, 0 };
	if (collider != nullptr && collider->colliderType != ColliderType::None)
		return collider->Move(this, move);
	else
		position += STA(move);
	return move;
}

sur::Object::~Object()
{
	delete boxHover, collider;
}