#pragma once
#include <RenderAnimal/RenderConstants.h>


namespace GamePlay
{
	class MeshComponent
	{
	public:

		MeshComponent();

		virtual ~MeshComponent();

		void AddVertices(std::vector<Constants::Vertex>&& InVertices);

		void AddIndices(std::vector<uint32_t> InIndices);

		std::vector<Constants::Vertex> mVertices;

		std::vector<uint32_t> mIndices;

		struct DrawCallParameters
		{
			UINT IndexCountPerInstance = 0;
			UINT InstanceCount = 0;
			UINT StartIndexLocation = 0;
			INT BaseVertexLocation = 0;
			UINT StartInstanceLocation = 0;
		} mDrawCallParameters;

	};
}
