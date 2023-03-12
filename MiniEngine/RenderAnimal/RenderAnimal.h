#pragma once
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
namespace RenderAnimal
{
	class Renderer
	{
	public:
		Renderer();
		~Renderer();

		void InitTargetWindow(HWND hwnd);

		void InitRenderer();

	private:

	};
}


