#pragma once
#include <string>
#include <array>
#include <cstdlib>
#include <functional>

namespace Sil
{
	class SilId
	{
	public:
		SilId() = default;
		//SilId(std::string_view id);

		const std::string ToString() const;

		//static SilId NewId();

		// Hashes a name to a 128-bit id
		static SilId FromName(std::string_view nameToHash);

		inline std::array<std::byte, 16>::iterator Begin() 
		{ 
			return _id.begin(); 
		}

		inline std::array<std::byte, 16>::iterator End()
		{
			return _id.end();
		}

		bool operator== (const SilId& other) const;
		
		friend std::hash<Sil::SilId>;

		bool IsEmpty() const { return _narrowId == 0; }
		
		static SilId Empty() {
			return {};
		}

	private:
		std::array<std::byte, 16> _id; // 128-bit hash
		size_t _narrowId = 0;
	};
}

template<>
struct std::hash<Sil::SilId>
{
	std::size_t operator()(const Sil::SilId& id) const noexcept
	{
		return id._narrowId;
	}
};