#pragma once
#include <Core/Interface.h>
#include <Core/System.h>
#include <Core/LinearAllocator.h>
#include <Core/GpuBuffer.h>
#include <Core/UploadBuffer.h>
#include <d3d12.h>


namespace RenderAnimal
{
	class Renderer : public Interface::Tickable, public Interface::System
	{
	public:
		Renderer();
		~Renderer();

		void InitTargetWindow(HWND hwnd,UINT width,UINT height);

		void InitRenderer();

		void InitPielineStates();

		// Inherited via Tickable
		virtual void Tick(float ms) override;

	private:
		ID3D12GraphicsCommandList* mGraphicsCmd = nullptr;

		ID3D12CommandAllocator* mGraphicsCmdAllocator = nullptr;

		UINT mFrameWidth = 0;

		UINT mFrameHeight = 0;

		D3D12_RECT mFrameRect = {};

		D3D12_VIEWPORT mViewPort = {};

		std::unique_ptr<ByteAddressBuffer> mVertexBuffer = nullptr;

		std::unique_ptr<ByteAddressBuffer> mIndexBuffer = nullptr;

		std::unique_ptr<VertexUploadBuffer> mUploadBuffer = nullptr;

		std::unique_ptr<IndexUploadBuffer> mUploadBufferIndex = nullptr;


		ID3D12PipelineState* mSimplePipelineState = nullptr;

		ID3D12RootSignature* mSimpleRS = nullptr;
	};
}


