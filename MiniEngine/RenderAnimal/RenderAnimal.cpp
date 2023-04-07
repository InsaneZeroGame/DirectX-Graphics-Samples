// RenderAnimal.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "RenderAnimal.h"
#include <Core/CommandListManager.h>
#include <Core/Display.h>
#include <Core/Utility.h>
#include <Core/GraphicsCore.h>
#include "RenderConstants.h"
#include <d3dcompiler.h>
#include <GamePlay/MeshComponent.h>

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
	mViewPort = {0,0,(float)mFrameWidth,(float)mFrameHeight,0,1};
}

void RenderAnimal::Renderer::InitRenderer()
{
	Initialize();
	InitPielineStates();
	g_CommandManager.CreateNewCommandList(D3D12_COMMAND_LIST_TYPE_DIRECT, &mGraphicsCmd, &mGraphicsCmdAllocator);
	mGraphicsCmd->Close();
	Display::Resize(mFrameWidth, mFrameHeight);
	mVertexBuffer = std::make_unique<ByteAddressBuffer>();
	mVertexBuffer->Create(L"Vertex Buffer", Constants::VERTEX_COUNT, sizeof(Constants::Vertex),nullptr);
	mUploadBuffer = std::make_unique<UploadBuffer>();
	mUploadBuffer->Create(L"Upload Buffer", Constants::UPLOAD_BUFFER_SIZE);

	//Upload
	{
		ID3D12CommandAllocator* lCmdAllocator = g_CommandManager.GetQueue().RequestAllocator();
		mGraphicsCmd->Reset(lCmdAllocator, nullptr);
		auto renderable = mRegistry.view<GamePlay::MeshComponent>();
		for (auto renderEntity : renderable)
		{
			auto& lComponent = renderable.get<GamePlay::MeshComponent>(renderEntity);
			mUploadBuffer->LoadMeshComponent(lComponent);

			mGraphicsCmd->CopyBufferRegion(mVertexBuffer->GetResource(), 0, mUploadBuffer->GetResource(), 0, mUploadBuffer->GetBufferSize());
			auto copyFence = g_CommandManager.GetGraphicsQueue().ExecuteCommandList(mGraphicsCmd);
			g_CommandManager.GetQueue().WaitForFence(copyFence);
			g_CommandManager.GetQueue().DiscardAllocator(copyFence, lCmdAllocator);
		}
	}
}

void RenderAnimal::Renderer::InitPielineStates()
{
	ID3DBlob* pOutBlob;
	ID3DBlob* pErrorBlob;
	D3D12_ROOT_SIGNATURE_DESC lSimpleRS = {};
	lSimpleRS.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
	D3D12SerializeRootSignature(&lSimpleRS, D3D_ROOT_SIGNATURE_VERSION_1,
		&pOutBlob, &pErrorBlob);
	Graphics::g_Device->CreateRootSignature(1, pOutBlob->GetBufferPointer(), pOutBlob->GetBufferSize(),
		MY_IID_PPV_ARGS(&mSimpleRS));
	ComPtr<ID3DBlob> vertexShader;
	ComPtr<ID3DBlob> pixelShader;

#if defined(_DEBUG)
	// Enable better shader debugging with the graphics debugging tools.
	UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
	UINT compileFlags = 0;
#endif

	// Define the vertex input layout.
	D3D12_INPUT_ELEMENT_DESC inputElementDescs[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0 },
	};

	D3DCompileFromFile(Utility::GetAssetFullPath(L"SimpleVertexShader.hlsl").c_str(),nullptr,nullptr,"main", "vs_5_0", compileFlags, 0, &vertexShader, nullptr);
	D3DCompileFromFile(Utility::GetAssetFullPath(L"SimplePixelShader.hlsl").c_str(), nullptr, nullptr, "main", "ps_5_0", compileFlags, 0, &pixelShader, nullptr);

	D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
	psoDesc.InputLayout = { inputElementDescs, _countof(inputElementDescs) };
	psoDesc.pRootSignature = mSimpleRS;
	psoDesc.VS = CD3DX12_SHADER_BYTECODE(vertexShader.Get());
	psoDesc.PS = CD3DX12_SHADER_BYTECODE(pixelShader.Get());
	psoDesc.RasterizerState = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
	psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
	psoDesc.DepthStencilState.DepthEnable = FALSE;
	psoDesc.DepthStencilState.StencilEnable = FALSE;
	psoDesc.SampleMask = UINT_MAX;
	psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
	psoDesc.NumRenderTargets = 1;
	psoDesc.RTVFormats[0] = DXGI_FORMAT_R10G10B10A2_UNORM;
	psoDesc.SampleDesc.Count = 1;	
	Graphics::g_Device->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&mSimplePipelineState));
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
		mGraphicsCmd->Reset(lCurrentCmdAllocator, mSimplePipelineState);
		//Present To RT
		auto lPresentToRT = Constants::PRESENT_TO_RT;
		lPresentToRT.Transition.pResource = Display::GetCurrentBackbuffer()->GetResource();
		mGraphicsCmd->ResourceBarrier(1, &lPresentToRT);

	}
	
	//On Render
	{
		mGraphicsCmd->SetPipelineState(mSimplePipelineState);
		mGraphicsCmd->SetGraphicsRootSignature(mSimpleRS);
		mGraphicsCmd->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		mGraphicsCmd->RSSetViewports(1, &mViewPort);
		mGraphicsCmd->RSSetScissorRects(1, &mFrameRect);
		mGraphicsCmd->OMSetRenderTargets(1, &currentBackbuffer, true, nullptr);
		mGraphicsCmd->ClearRenderTargetView(currentBackbuffer, clearColor, 1, &mFrameRect);
		D3D12_VERTEX_BUFFER_VIEW vertexBuffers[] = { mVertexBuffer->VertexBufferView() };
		mGraphicsCmd->IASetVertexBuffers(0, 1, vertexBuffers);

		auto renderable = mRegistry.view<GamePlay::MeshComponent>();
		for (auto renderableEntity : renderable)
		{
			auto [meshComponent] = renderable.get(renderableEntity);
			mGraphicsCmd->DrawInstanced(
				meshComponent.mDrawCallParameters.VertexCountPerInstance,
				1,
				meshComponent.mDrawCallParameters.StartVertexLocation,
				0);
		}
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