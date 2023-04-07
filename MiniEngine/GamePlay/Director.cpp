#include "pch.h"
#include "Director.h"
namespace GamePlay
{
	Director Director::mInstance;
	std::once_flag Director::mCallOnce;
}

GamePlay::Director::Director()
{

}

GamePlay::Director::~Director()
{

}

GamePlay::Director& GamePlay::Director::GetDirector()
{
	std::call_once(mCallOnce, []() { static Director mInstance; });
	return mInstance;
}

void GamePlay::Director::LoadLevel()
{
	Level OneLevel;
	OneLevel.mAsset.entity = mRegistry.create();
	auto& lComponent = mRegistry.emplace_or_replace<MeshComponent>(OneLevel.mAsset.entity);
	lComponent.AddVertices(std::move(OneLevel.mAsset.meshInfo.vertices));
	mLevels.push_back(OneLevel);
}
