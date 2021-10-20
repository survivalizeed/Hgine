

#include "IniReader.h"

sur::IniReader::IniReader(std::string_view filename)
{
	this->filename = filename;
	std::ifstream file(filename.data());
	std::stringstream ss;
	ss << file.rdbuf();
	std::string item;
	while (std::getline(ss, item, ' ')) {
		if (item == "")
			continue;
		words.push_back(item);
	}
}

std::string sur::IniReader::getEntry(std::string_view name)
{
	for (int i = 0; i < words.size(); ++i) {
		if (words[i] == name) {
			return words[static_cast<size_t>(i) + 2];
		}
	}
}

