

#include "../Objects.h"

sur::Camera::Camera(Vec2f position, bool active)
{
	this->position = position;
	if(active)
		_active_camera = this;
	_cameras.push_back(this);
}

void sur::Camera::MakeActive()
{
	_active_camera = this;
	Vec2f tmp(position);
	tmp.invert();
	_camera_offset = ATS(tmp);
}

void sur::Camera::SetPosition(Vec2f position)
{
	this->position = position;
	if (_active_camera == this) {
		Vec2f tmp(position);
		tmp.invert();
		_camera_offset = ATS(tmp);
	}
}

sur::Vec2f sur::Camera::GetPosition()
{
	return position;
}

sur::Vec2 sur::Camera::Move(Vec2f direction, i32 moveQueueIndex)
{
	Vec2 move = MoveQueue(direction, moveQueueIndex);
	if (move.x == 0 && move.y == 0) return { 0, 0 };
	position += STA(move);
	if (_active_camera == this) {
		Vec2f tmp(position);
		tmp.invert();
		_camera_offset = ATS(tmp);
	}
	return move;
}
