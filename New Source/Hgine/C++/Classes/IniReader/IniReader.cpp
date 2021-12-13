

#include "IniReader.h"

sur::IniReader::IniReader(std::string_view filename)
{
	this->filename = filename;
	std::ifstream file(filename.data());
	if (!file) {
		Error("Unable to read file");
	}
	std::stringstream ss;
	ss << file.rdbuf();
	std::string item;

	auto SplitOnChar = [](const std::vector<std::string>& input, const std::string& splitString) -> std::vector<std::string>
	{
		std::vector<std::string> output;
		for (std::vector<std::string>::const_iterator it = input.begin(); it != input.end(); ++it)
		{
			std::string::size_type pos = it->find(splitString);
			if (pos != std::string::npos)
			{
				output.push_back(it->substr(0, pos));
				output.push_back(splitString);
				output.push_back(it->substr(pos + splitString.size()));
			}
			else
			{
				output.push_back(*it);
			}
		}
		return output;
	};

	while (std::getline(ss, item, ' ')) {
		if (item == "")
			continue;
		words.push_back(item);
	}
	words = SplitOnChar(words, "\n");
}

std::string sur::IniReader::getEntry(std::string_view name)
{
	for (int i = 0; i < words.size(); ++i) {
		if (words[i] == name) {
			return words[static_cast<size_t>(i) + 2];
		}
	}
}

