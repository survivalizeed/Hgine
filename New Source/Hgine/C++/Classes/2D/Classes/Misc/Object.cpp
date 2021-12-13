

#include "../Objects.h"

void sur::Object::DoRelevantChecks() 
{
	if (boxHover != nullptr)
		boxHover->CheckHover();
	if (collider != nullptr)
		collider->CheckCollision();
}

sur::Color sur::Object::TintPixel(Color color)
{
    if (tint == H_RGB(0, 0, 0))
        return color;
    H_RGB tmp(0, 0, 0);
    tmp.ToRGB(color);
    tmp = tmp + tint;
    if (tmp.r > 255)
        tmp.r = 255;
    if (tmp.r < 0)
        tmp.r = 0;
    if (tmp.g > 255)
        tmp.g = 255;
    if (tmp.g < 0)
        tmp.g = 0;
    if (tmp.b > 255)
        tmp.b = 255;
    if (tmp.b < 0)
        tmp.b = 0;
    Color c = Color(tmp.r, tmp.g, tmp.b);
    return c;
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

void sur::Object::SetPosition(Vec2f position)
{
    if (childOfCamera) {
        original_position = position + STA(_camera_offset);
    }
    this->position = position;
}

sur::Vec2 sur::Object::Move(Vec2f direction, i32 moveQueueIndex)
{
	Vec2 move = MoveQueue(direction, moveQueueIndex);
	if (move.x == 0 && move.y == 0) return { 0, 0 };
	if (collider != nullptr && collider->colliderType != ColliderType::None)
		return collider->Move(this, move);
    else {
        position += STA(move);
        original_position += STA(move);
    }
	return move;
}

void sur::Object::Bind()
{
    switch (type)
    {
    case sur::Type::Square:
        static_cast<Square*>(this)->Bind();
        break;
    case sur::Type::Line:
        static_cast<Line*>(this)->Bind();
        break;
    case sur::Type::Triangle:
        static_cast<Triangle*>(this)->Bind();
        break;
    case sur::Type::Form:
        static_cast<Form*>(this)->Bind();
        break;
    case sur::Type::Sprite:
        static_cast<Sprite*>(this)->Bind();
        break;
    case sur::Type::ParticleSystem:
        static_cast<ParticleSystem*>(this)->Bind();
        break;
    case sur::Type::Light:
        static_cast<Light*>(this)->Bind();
        break;
    case sur::Type::Text:
        static_cast<Text*>(this)->Bind();
        break;
    case sur::Type::Camera:
        static_cast<Camera*>(this)->Bind();
        break;
    case sur::Type::InputBox:
        break;
    }
}

sur::Object::~Object()
{
	delete boxHover, collider;
}