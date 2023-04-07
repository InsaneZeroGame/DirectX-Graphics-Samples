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

		std::vector<Constants::Vertex> mVertices;

		struct DrawCallParameters
		{
			UINT VertexCountPerInstance;
			UINT StartVertexLocation;
		} mDrawCallParameters;

	};
}
