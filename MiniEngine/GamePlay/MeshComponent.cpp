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
