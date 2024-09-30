#include "Debug/Logger.h"
#include <iostream>

namespace Sil
{
	std::string_view GetPrefix(Sil::Verbosity type)
	{
		switch (type)
		{
			case Message: return "Message: ";
			case Warning: return "Warning: ";
			case Error: return "Error: ";
		}

		return "";
	}

	void Sil::Log(Sil::Verbosity type, const std::string_view message)
	{
		std::cout << GetPrefix(type) << message;
	}

	void Sil::LogMessage(const std::string_view message) { Log(Verbosity::Message, message); }
	void Sil::LogWarning(const std::string_view warning) { Log(Verbosity::Warning, warning); }
	void Sil::LogError(const std::string_view error) { Log(Verbosity::Error, error); }
}