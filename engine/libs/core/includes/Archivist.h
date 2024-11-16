#pragma once
#include <unordered_map>
#include <typeindex>
#include <type_traits>
#include <memory>
#include <stdexcept>
#include <format>

namespace Sil
{	
	template <typename T>
	concept Service = std::is_class_v <T>;

	class Archivist
	{
	public:
		template <Service TService>
		void Archive(std::shared_ptr<TService> service)
		{
			const auto& id = typeid(TService);
			if (_services.contains(id) == false)
			{
				_services.emplace({ id, std::static_pointer_cast<void>(service)});
			}

			throw std::runtime_error(std::format("Cannot archive type {}, an object of that type is already archived.", id.name()));
		}

		template <Service TService>
		std::shared_ptr<TService> Retreive()
		{
			const auto& id = typeid(TService);
			if (auto& search = _services.find(id) != _services.end())
			{
				return std::static_pointer_cast<TService>(search->second)
			}

			throw std::runtime_error(std::format("Cannot find type {} in archive.", id.name()));
		}

		template <Service TService>
		void Delete()
		{
			const auto& id = typeid(TService);
			if (_services.contains(id))
			{
				_services.erase(id);
			}
		}

	private:
		std::unordered_map<type_info, std::shared_ptr<void>> _services;
	};

	static Archivist ProjectArchivist;
}