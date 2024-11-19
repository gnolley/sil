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

		// Registers a service with this archive, which can be retrieved later.
		template <Service TService>
		void Archive(std::shared_ptr<TService> service)
		{
			const auto id = std::type_index(typeid(TService));
			if (_services.contains(id) == false)
			{
				_services.emplace(std::pair<std::type_index, std::shared_ptr<void>>(
					id, std::static_pointer_cast<void>(service)));
			}

			throw std::runtime_error(std::format("Cannot archive type {}, an object of that type is already archived.", id.name()));
		}

		// Returns an archived service
		template <Service TService>
		std::shared_ptr<TService> Retrieve()
		{
			const auto id = std::type_index(typeid(TService));
			if (const auto search = _services.find(id); search != _services.end())
			{
				return std::static_pointer_cast<TService>(search->second);
			}

			throw std::runtime_error(std::format("Cannot find type {} in archive.", id.name()));
		}

		// Deletes an archived service.
		template <Service TService>
		void Delete()
		{
			if (const auto& id = std::type_index(typeid(TService)); _services.contains(id))
			{
				_services.erase(id);
			}
		}

	private:
		std::unordered_map<std::type_index, std::shared_ptr<void>> _services;
	};

	static Archivist ProjectArchivist;
}