

#include "../Objects.h"

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
