#pragma once

#include <string_view>

namespace Sil
{
	enum Verbosity
	{
		Info = 0,
		Message = 1,
		Warning = 2,
		Error = 3,
	};

	inline void Log(Verbosity type, const std::string_view message);

	void LogInfo(const std::string_view message);
	void LogMessage(const std::string_view message);
	void LogWarning(const std::string_view warning);
	void LogError(const std::string_view error);
}