#pragma once
#include <string_view>
#include <string>
#include <unordered_map>
#include <filesystem>

namespace filesystem = std::filesystem;

namespace Stagehand
{
	template<typename TFuncType>
	TFuncType GetFallbackFunc();

	template<typename TFuncType>
	std::unordered_map<std::string_view, TFuncType> GetFuncMap();

	template<typename TFuncType>
	TFuncType SelectExtProcess(filesystem::path& fileExtension, const std::unordered_map<std::string_view, TFuncType>& map)
	{
		std::string extension = fileExtension.string();
		if (map.contains(extension))
		{
			return map.at(extension);
		}

		return GetFallbackFunc<TFuncType>();
	}

	template<typename TFuncType>
	TFuncType SelectExtProcess(filesystem::path& fileExtension)
	{
		auto map = GetFuncMap<TFuncType>();
		return SelectExtProcess<TFuncType>(fileExtension, map);
	}
}