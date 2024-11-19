#pragma once
#include <vulkan/vulkan.h>
#include "Rendering/GraphicsDevice.h"

namespace Sil
{
    class VkShaderModule
    {
        public:
            VkShaderModule(const VkShaderModuleCreateInfo info, const GraphicsDevice& device)
                : _device(device)
            {
                if(vkCreateShaderModule(device.GetDevice(), &info, nullptr, &_shaderModule) != VK_SUCCESS)
                {
                    throw std::runtime_error("failed to create shader module!");
                }
            }

            VkShaderModule(const VkShaderModule& other) = delete;

            ~VkShaderModule()
            {
                vkDestroyShaderModule(_device.GetDevice(), _shaderModule, nullptr);
            }

            [[nodiscard]] ::VkShaderModule GetModule()  const { return _shaderModule; }

        private:
            ::VkShaderModule _shaderModule;
            const GraphicsDevice& _device;
    };
}