// RenderAnimal.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "framework.h"
#include "RenderAnimal.h"
#include "../Core/CommandListManager.h"
#include "../Core/Display.h"
#include "RenderConstants.h"

using namespace Utility;
using namespace Graphics;
// TODO: This is an example of a library function
void fnRenderAnimal()
{
}

RenderAnimal::Renderer::Renderer()
{
	Constants::InitConstants();
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
	mGraphicsCmd->Close();
	Display::Resize(mFrameWidth, mFrameHeight);
}

void RenderAnimal::Renderer::Tick(float ms)
{
	//Printf("Tick delta : %f\n", ms);
	float clearColor[4] = {0.0,1.0,0.0,1.0};
	const auto [currentBackbuffer,bufferIndex] = Display::GetCurrentBackbufferHandle();
	auto& graphicsCmdQueue = g_CommandManager.GetGraphicsQueue();
	ID3D12CommandAllocator* lCurrentCmdAllocator = graphicsCmdQueue.RequestAllocator();

	//Pre Render
	{
		mGraphicsCmd->Reset(lCurrentCmdAllocator, nullptr);
	}
	
	//On Render

	{
		auto lPresentToRT = Constants::PRESENT_TO_RT;
		auto lRTToPresent = Constants::RT_TO_PRESENT;
		lPresentToRT.Transition.pResource = Display::GetCurrentBackbuffer()->GetResource();
		lRTToPresent.Transition.pResource = Display::GetCurrentBackbuffer()->GetResource();
		mGraphicsCmd->ResourceBarrier(1, &lPresentToRT);
		mGraphicsCmd->ClearRenderTargetView(currentBackbuffer, clearColor, 1, &mFrameRect);
		mGraphicsCmd->ResourceBarrier(1, &lRTToPresent);
	}
	
	//Post Render
	{
		auto fenceValue = graphicsCmdQueue.ExecuteCommandList(mGraphicsCmd);
		Display::Present();
		graphicsCmdQueue.DiscardAllocator(fenceValue, lCurrentCmdAllocator);
	}
}