

#pragma once

#if _WIN32 || _WIN64
#if _WIN64
#else

#include "../../../Includes.h"

namespace sur
{
	enum class AngelDatatype 
	{

		Int,
		Long,
		Float,
		Double,
		Bool,
		Void

	};

	class AngelScript
	{

		asIScriptModule* mod;
		asIScriptContext* ctx;

		std::map<std::string, asIScriptFunction*> functions;

	public:

		AngelScript(std::string_view fileName, std::vector<std::string_view> registeredFunctionDecls, std::vector<void*> functions);

		void AddFunction(std::string_view alias, std::string_view declName);

		template<AngelDatatype type>
		auto CallFunction(std::string_view alias, std::string_view parameters) 
		{
			auto StringStartsWith = [](std::string_view data, std::string_view startwith) -> bool
			{
				for (int i = 0; i < startwith.size(); ++i)
					if (data[i] != startwith[i])
						return false;
				return true;
			};
			auto GetStringBetweenChars = [](std::string_view data, char c1, char c2) -> std::string
			{
				bool found = false;
				std::string tmp;
				for (int i = 0; i < data.size(); ++i) {
					if (data[i] == c2)
						return tmp;
					if (data[i] == c1)
						found = true;
					else if (found)
						tmp += data[i];
				}
			};

			ctx->Prepare(functions[alias.data()]);
			std::stringstream ss(parameters.data());
			std::string tmp;
			std::vector<std::string> words;
			while (std::getline(ss, tmp, ' ')) {
				words.push_back(tmp);
			}
			int counter = 0;
			for (auto& iter : words) {
				if (StringStartsWith(iter, "int")) {
					ctx->SetArgDWord(counter, stoi(GetStringBetweenChars(iter, '(', ')')));
				}
				else if (StringStartsWith(iter, "long")) {
					ctx->SetArgQWord(counter, stol(GetStringBetweenChars(iter, '(', ')')));
				}
				else if (StringStartsWith(iter, "float")) {
					ctx->SetArgFloat(counter, stof(GetStringBetweenChars(iter, '(', ')')));
				}
				else if (StringStartsWith(iter, "double")) {
					ctx->SetArgDouble(counter, stod(GetStringBetweenChars(iter, '(', ')')));
				}
				else if (StringStartsWith(iter, "bool")) {
					ctx->SetArgByte(counter, stoi(GetStringBetweenChars(iter, '(', ')')));
				}
				++counter;
			}
			ctx->Execute();

			if constexpr (type == AngelDatatype::Int)
				return ctx->GetReturnDWord();
			if constexpr (type == AngelDatatype::Long)
				return ctx->GetReturnQWord();
			if constexpr (type == AngelDatatype::Float)
				return ctx->GetReturnFloat();
			if constexpr (type == AngelDatatype::Double)
				return ctx->GetReturnDouble();
			if constexpr (type == AngelDatatype::Bool)
				return ctx->GetReturnByte();
			if constexpr (type == AngelDatatype::Void)
				return;
		}

		void Release();

	};
}
#endif
#endif