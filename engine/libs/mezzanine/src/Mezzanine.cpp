#include "Mezzanine.h"
#include "Debug/Logger.h"
#include <iostream>
#include <format>
#include <Archivist.h>
#include <AssetToken.h>
#include <memory>
#include <Playbook.h>

#include "Rendering/Shader.h"

namespace Sil
{
	Mezzanine::Mezzanine(const RenderConfig& config, const Window& window)
		: _graphicsContext(config, window), _colorPass(_graphicsContext)
	{
		LogInfo(std::format("Mezzanine Initialised. Extensions: {0}, Layers {1}",
			_graphicsContext.NumEnabledExtensions(), _graphicsContext.NumEnabledValidationLayers()));

		_locator = std::make_shared<GraphicsLocator>(_graphicsContext, _colorPass);
		ProjectArchivist.Archive<GraphicsLocator>(_locator);
	}

	void Mezzanine::DisplaySplashScreen()
	{
		Shader splashScreenShader = Shader( {
			SilId::FromName("SplashScreen_frag.spv"),
			SilId::FromName("SplashScreen_vert.spv"),
			CullMode::Back,
			false,
			BlendMode::Additive,
			BlendMode::Additive,
			0.f
		}, _graphicsContext);
	}
}
