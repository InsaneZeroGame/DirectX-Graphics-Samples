#pragma once
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include "../Core/Interface.h"


namespace RenderAnimal
{
	class Renderer : public Interface::Tickable
	{
	public:
		Renderer();
		~Renderer();

		void InitTargetWindow(HWND hwnd);

		void InitRenderer();

		// Inherited via Tickable
		virtual void Tick(float ms) override;

	private:
	};
}


