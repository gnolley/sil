#pragma once
#include <GLFW/glfw3.h>
#include <stdexcept>
#include "Debug/Logger.h"

namespace Sil
{
	class GLFWInstance
	{
	public:
		GLFWInstance()
		{
			auto result = glfwInit();
			if (result != GLFW_TRUE)
			{
				throw std::runtime_error("GLFW could not initialise!");
			}

			LogInfo("GLFW Initialised");

			glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		}

		~GLFWInstance()
		{
			glfwTerminate();
		}

		void PollEvents()
		{
			glfwPollEvents();
		}
	};
}