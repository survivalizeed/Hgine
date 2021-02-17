

#pragma once

#include "includes.h"

namespace sur {
	sur::Maps Initialize();

	int CharCounter(char Char, std::string Data);

	template<typename T>
	size_t Hash(T& Content, std::string id)
	{
		int count = 0;
		std::string chars = "abcdefghijklmnopqrstuvwxyz";
		for (int i = 0; i < chars.size(); i++) {
			count += CharCounter(chars[i], id) * CharCounter(chars[i], id);
		}
		return sizeof(Content) * id.size() - (sizeof(Content) / 2) + count;
	}
}