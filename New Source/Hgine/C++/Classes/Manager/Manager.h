

#pragma once

#include "../../../Includes.h"

namespace sur
{
	enum class Type;
}

namespace sur::Manager
{

	void Add(void* object, Type type);

	void Remove(Type type, std::string_view name, i32 index = -1);

	void Delete(Type type, std::string_view name, i32 index = -1);

	void RemoveAll();

	void DeleteAll();

	template<typename RetValue>
	RetValue* Get(std::string_view name, i32 index = -1);
}