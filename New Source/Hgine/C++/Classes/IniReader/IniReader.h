

#pragma once

#include "../../../Includes.h"

namespace sur
{
	class IniReader
	{
	private:

		std::string filename;
		std::vector<std::string> words;

	public:

		IniReader(std::string_view filename);

		std::string getEntry(std::string_view name);

	};
}

