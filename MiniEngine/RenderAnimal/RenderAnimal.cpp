// RenderAnimal.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#include "RenderAnimal.h"
#include "../Core/CommandListManager.h"
#include "../Core/Display.h"

using namespace Utility;
using namespace Graphics;
// TODO: This is an example of a library function
void fnRenderAnimal()
{
}

RenderAnimal::Renderer::Renderer()
{
}

RenderAnimal::Renderer::~Renderer()
{
	Shutdown();
}


void RenderAnimal::Renderer::InitTargetWindow(HWND hwnd, UINT width, UINT height)
{
	SetPhysicalWindow(hwnd);
	mFrameHeight = height;
	mFrameWidth = width;
	mFrameRect = {0,0,(LONG)mFrameWidth,(LONG)mFrameHeight };
}

void RenderAnimal::Renderer::InitRenderer()
{
	Initialize();
	g_CommandManager.CreateNewCommandList(D3D12_COMMAND_LIST_TYPE_DIRECT, &mGraphicsCmd, &mGraphicsCmdAllocator);
	Display::Resize(mFrameWidth, mFrameHeight);
}

void RenderAnimal::Renderer::Tick(float ms)
{
	Printf("Tick delta : %f\n", ms);
	float clearColor[4] = {0.0,1.0,0.0,1.0};
	mGraphicsCmd->ClearRenderTargetView(g_DisplayPlane[GetFrameCount() % SWAP_CHAIN_BUFFER_COUNT].GetRTV(),clearColor,1,&mFrameRect);
	ID3D12CommandList* lCmd[] = {mGraphicsCmd};
	g_CommandManager.GetCommandQueue()->ExecuteCommandLists(1, lCmd);
	Display::Present();
}