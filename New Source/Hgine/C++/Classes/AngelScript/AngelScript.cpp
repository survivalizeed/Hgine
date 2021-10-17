
#if _WIN32 || _WIN64
#if _WIN64
#else

#include "AngelScript.h"


sur::AngelScript::AngelScript(std::string_view fileName, std::vector<std::string_view> registeredFunctionDecls, std::vector<void*> functions)
{
	for (int i = 0; i < registeredFunctionDecls.size(); ++i) {
		_asEngine->RegisterGlobalFunction(registeredFunctionDecls[i].data(), asFUNCTION(functions[i]), asCALL_CDECL);
	}
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

void sur::AngelScript::AddFunction(std::string_view alias ,std::string_view declName)
{
	functions[alias.data()] = mod->GetFunctionByDecl(declName.data());
}

void sur::AngelScript::Release()
{
	ctx->Release();
}

#endif
#endif