#pragma once
#include "Rendering/GraphicsContext.h"
#include "Rendering/RenderPass.h"

namespace Sil
{
	class GraphicsLocator
	{
	public:
		GraphicsLocator(const GraphicsContext& context, const RenderPass& colorPass)
			: _context(context), _colorPass(colorPass)
		{
		}

		[[nodiscard]] const GraphicsContext& GetContext() const { return _context; }
		[[nodiscard]] const RenderPass& GetColorPass() const { return _colorPass; }

	private:
		const GraphicsContext& _context;
		const RenderPass& _colorPass;
	};
}