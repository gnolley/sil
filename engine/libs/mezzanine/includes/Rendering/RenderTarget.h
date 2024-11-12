#pragma once
#include <vulkan/vulkan_core.h>

namespace Sil
{
	class RenderTarget
	{
	public: 
		VkFormat GetFormat() const
		{
			return _targetFormat;
		}

	protected:
		VkFormat _targetFormat;
	};
}