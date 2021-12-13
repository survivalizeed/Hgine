

#pragma once

#include "../../../Includes.h"

namespace sur
{
	enum class Type;
}

namespace sur::Manager
{

	void Add(Object* object);

	template<typename RetValue>
	RetValue* Get(std::string_view name, i32 index = -1);

	void Bind();

	void SetActive(bool state, std::string_view name);

	void Remove(std::string_view name, i32 index = -1);

	void Delete(std::string_view name, i32 index = -1);

	void RemoveAll();

	void DeleteAll();

}