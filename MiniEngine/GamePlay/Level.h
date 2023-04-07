#pragma once
#include <Core/Interface.h>
#include "MeshComponent.h"


namespace GamePlay              
{
	class Level : public Interface::Tickable
	{
	public:
		Level();
		virtual ~Level();
		// Inherited via Tickable
		virtual void Tick(float ms) override;

		struct Asset
		{
			enum class entt::entity entity;
			struct MeshInfo {
				std::vector<Constants::Vertex> vertices;
			} meshInfo;
		}mAsset;

	protected:
		
	private:

		
	};
}

