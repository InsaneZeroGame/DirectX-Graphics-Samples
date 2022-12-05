#pragma once
#include "../EngineCore/IModule.h"


namespace RenderAnimal
{

	class RendererCore final : public EngineCore::Singleton<RendererCore>
	{
	public:
		~RendererCore() {};
		RendererCore() {};

	private:

	};
}
