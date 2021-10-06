

#pragma once

#include "../../../Includes.h"

class AngelScript
{
	asIScriptModule* mod;
	asIScriptContext* ctx;

	std::map<std::string, asIScriptFunction*> functions;

public:

	AngelScript(std::string_view fileName);

	void AddFunction(std::string_view alias, std::string_view declName);

	void* CallFunction(std::string_view alias, const std::string& parameters);

};