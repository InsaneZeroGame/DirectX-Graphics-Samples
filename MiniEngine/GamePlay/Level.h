#pragma once
#include <Core/Interface.h>


namespace GamePlay
{
	class Level : public Interface::Tickable
	{
	public:
		Level();
		virtual ~Level();
		// Inherited via Tickable
		virtual void Tick(float ms) override;
	protected:
		
	private:

		
	};
}

