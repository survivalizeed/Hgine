

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
