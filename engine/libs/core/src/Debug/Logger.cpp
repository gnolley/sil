#include "Debug/Logger.h"
#include <iostream>

namespace Sil
{
	std::string_view GetPrefix(Sil::Verbosity type)
	{
		switch (type)
		{
			case Info: return "\033[37mInfo: ";
			case Message: return "\033[97mMessage: ";
			case Warning: return "\033[93mWarning: ";
			case Error: return "\033[91mError: ";
		}

		return "";
	}

	std::ostream& GetStream(Sil::Verbosity type)
	{
		switch (type)
		{
			case Info:
			case Message:
			case Warning:
				return std::cout;

			case Error:
				return std::cerr;
		}

		return std::cout;
	}

	void Sil::Log(Sil::Verbosity type, const std::string_view log)
	{
		GetStream(type) << GetPrefix(type) << log << "\n";
	}

	void Sil::LogInfo(const std::string_view info) { Log(Verbosity::Info, info); }
	void Sil::LogMessage(const std::string_view message) { Log(Verbosity::Message, message); }
	void Sil::LogWarning(const std::string_view warning) { Log(Verbosity::Warning, warning); }
	void Sil::LogError(const std::string_view error) { Log(Verbosity::Error, error); }
}