

#include "../Objects.h"


sur::Collider::Collider(Object* objectToAttachTo, Vec2f start, Vec2f end, ColliderType colliderType)
{
	this->objectToAttachTo = objectToAttachTo;
	this->start = start;
	this->end = end;
	this->colliderType = colliderType;
}

void sur::Collider::CheckCollision()
{
	anyCollisionLeft = false;

	for (i32 i = static_cast<i32>(previousCall.size()); i < _objects.size(); ++i) {
		previousCall.push_back(false);
		collided.push_back(false);
	}
	for (i32 i = 0; i < collided.size(); ++i) {
		collided[i] = false;
	}
	for (i32 i = 0; i < _objects.size(); ++i) {
		if (objectToAttachTo == _objects[i] || (_objects[i]->collider == nullptr || _objects[i]->collider->colliderType != ColliderType::AABB))
			continue;
		if (algorithm::AABB(start - STA({ 1,1 }) + objectToAttachTo->position, end + STA({ 1,1 }) + objectToAttachTo->position,
			_objects[i]->collider->start + _objects[i]->position, _objects[i]->collider->end + _objects[i]->position)) {
			if (!previousCall[i]) {
				if (this->onCollisionEnter != nullptr)
					this->onCollisionEnter(objectToAttachTo, _objects[i]);
			}

			if (this->onCollisionStay != nullptr)
				this->onCollisionStay(objectToAttachTo, _objects[i]);
			collided[i] = true;
			anyCollisionLeft = true;
		}
	}
	for (i32 i = 0; i < collided.size(); ++i)
		if (collided[i] && objectToAttachTo != _objects[i])
			previousCall[i] = true;

	for (i32 i = 0; i < collided.size(); ++i) {
		if (!collided[i] && previousCall[i] && objectToAttachTo != _objects[i]) {
			if (this->onCollisionExit != nullptr)
				this->onCollisionExit(objectToAttachTo, _objects[i]);
			previousCall[i] = false;
		}
	}

}

sur::Vec2 sur::Collider::Move(sur::Object* current, Vec2 incomingDirection) {

	auto MakeAABB = [](sur::Object* first, sur::Object* second) -> bool
	{
		Vec2f fsta = first->collider->start + first->position;
		Vec2f fend = first->collider->end + first->position;

		Vec2f ssta = second->collider->start + second->position;
		Vec2f send = second->collider->end + second->position;

		return algorithm::AABB(fsta, fend, ssta, send);
	};

	auto MakeSTA = [](sur::Object* first, sur::Object* second) -> bool
	{
		//Insert STA code

		return false;
	};

	bool alreadyDecreased = false;
	for (i32 i = 0; i < _objects.size(); ++i) {
		if (objectToAttachTo == _objects[i] || (_objects[i]->collider == nullptr || _objects[i]->collider->colliderType != ColliderType::AABB))
			continue;
		objectToAttachTo->position += STA(incomingDirection);
		while (MakeAABB(objectToAttachTo, _objects[i])) {
			objectToAttachTo->position -= STA(incomingDirection);
			alreadyDecreased = true;
			incomingDirection.closerToZeroByOne();
			if (incomingDirection.isZero())
				break;
		}
		if (!alreadyDecreased)
			objectToAttachTo->position -= STA(incomingDirection);
		alreadyDecreased = false;
	}
	objectToAttachTo->position += STA(incomingDirection);
	return incomingDirection;
}
