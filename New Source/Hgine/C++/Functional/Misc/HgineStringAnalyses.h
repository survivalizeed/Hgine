#pragma once

#include "../../../Includes.h"

namespace sur::str
{
    inline std::string GetSubStringBetweenStrings(const std::string& input, std::string_view start, std::string_view end)
    {
        u32 startPos = static_cast<u32>(input.find(start));
        if (startPos == std::string::npos) return "";
        startPos += static_cast<u32>(start.size());
        u32 endPos = static_cast<u32>(input.find(end, startPos));
        if (endPos == std::string::npos) return "";
        return input.substr(startPos, static_cast<size_t>(endPos - startPos));
    }

    inline std::string RemoveSubStringBetweenStrings(const std::string& input, std::string_view start, std::string_view end)
    {
        u32 startPos = static_cast<u32>(input.find(start));
        if (startPos == std::string::npos) return "";
        startPos += static_cast<u32>(start.size());
        u32 endPos = static_cast<u32>(input.find(end, startPos));
        if (endPos == std::string::npos) return "";
        return input.substr(0, startPos - 1) + input.substr(endPos + end.size());
    }

    inline auto SplitStringToVectorIfChar(std::string_view input, char splitChar)
    {
        std::vector<std::string> output;
        std::string temp;
        for (i32 i = 0; i < input.size(); ++i) {
            if (input[i] == splitChar) {
                output.push_back(temp);
                temp = "";
            }
            else temp += input[i];
        }
        output.push_back(temp);
        return output;
    }
}