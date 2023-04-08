#pragma once

#include "pch.h"


namespace Constants
{
	struct Vertex
	{
		std::array<float, 4> pos;
	};

	extern const UINT VERTEX_COUNT;
	extern const UINT UPLOAD_BUFFER_SIZE;
	extern D3D12_RESOURCE_BARRIER PRESENT_TO_RT;
	extern D3D12_RESOURCE_BARRIER RT_TO_PRESENT;
	extern D3D12_RESOURCE_BARRIER TO_INDEX_BUFFER;


	void InitConstants();
	
}

