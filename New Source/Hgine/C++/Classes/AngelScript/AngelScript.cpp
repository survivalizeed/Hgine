

#include "AngelScript.h"

AngelScript::AngelScript(std::string_view fileName)
{
	mod = _asEngine->GetModule(fileName.data(), asGM_ALWAYS_CREATE);
	std::ifstream i(fileName.data());
	if (!i)
		return;
	std::stringstream ss;
	ss << i.rdbuf();
	mod->AddScriptSection(fileName.data(), ss.str().c_str());
	mod->Build();
	ctx = _asEngine->CreateContext();
}

void AngelScript::AddFunction(std::string_view alias ,std::string_view declName)
{
	functions[alias.data()] = mod->GetFunctionByDecl(declName.data());
}

void* AngelScript::CallFunction(std::string_view alias, const std::string& parameters)
{
	ctx->prepare(functions[alias.data()];
	
}
