#include "pch.h"
#include "MeshComponent.h"



GamePlay::MeshComponent::MeshComponent()
{

}

GamePlay::MeshComponent::~MeshComponent()
{

}

void GamePlay::MeshComponent::AddVertices(std::vector<Constants::Vertex>&& InVertices)
{
	mVertices = InVertices;
}

void GamePlay::MeshComponent::AddIndices(std::vector<uint32_t> InIndices)
{
	mIndices = InIndices;
}
