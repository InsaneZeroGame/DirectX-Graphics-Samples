// RenderAnimal.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "RenderAnimal.h"
#include <Core/CommandListManager.h>
#include <Core/Display.h>
#include <Core/Utility.h>
#include <Core/GraphicsCore.h>
#include "RenderConstants.h"

using namespace Utility;
using namespace Graphics;

const UINT kCpuSize = 10 * 1024 * 1024;


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
	mCpuAllocator = std::make_unique<LinearAllocator>(kCpuWritable);
	mCpuAllocator->Allocate(kCpuSize);
	mGpuAllocator = std::make_unique<LinearAllocator>(kGpuExclusive);
	mGpuAllocator->Allocate(kCpuSize);
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
		//Present To RT
		auto lPresentToRT = Constants::PRESENT_TO_RT;
		lPresentToRT.Transition.pResource = Display::GetCurrentBackbuffer()->GetResource();
		mGraphicsCmd->ResourceBarrier(1, &lPresentToRT);

	}
	
	//On Render

	{
		mGraphicsCmd->ClearRenderTargetView(currentBackbuffer, clearColor, 1, &mFrameRect);
	}
	
	//Post Render
	{
		//RT To Present
		auto lRTToPresent = Constants::RT_TO_PRESENT;
		lRTToPresent.Transition.pResource = Display::GetCurrentBackbuffer()->GetResource();
		mGraphicsCmd->ResourceBarrier(1, &lRTToPresent);

		//Flush cmd and discard cmd allocator.
		auto fenceValue = graphicsCmdQueue.ExecuteCommandList(mGraphicsCmd);
		Display::Present();
		graphicsCmdQueue.DiscardAllocator(fenceValue, lCurrentCmdAllocator);
	}
}