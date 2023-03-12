// RenderAnimal.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#include "RenderAnimal.h"
#include <Core/GraphicsCore.h>


// TODO: This is an example of a library function
void fnRenderAnimal()
{
}

RenderAnimal::Renderer::Renderer()
{
}

RenderAnimal::Renderer::~Renderer()
{
	Graphics::Shutdown();
}


void RenderAnimal::Renderer::InitTargetWindow(HWND hwnd)
{
	Graphics::SetPhysicalWindow(hwnd);
}

void RenderAnimal::Renderer::InitRenderer()
{
	Graphics::Initialize();
}
