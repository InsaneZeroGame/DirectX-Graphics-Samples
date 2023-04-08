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
	lComponent.AddIndices(std::move(OneLevel.mAsset.meshInfo.indices));

	OneLevel.mAsset1.entity = mRegistry.create();
	auto& lComponent1 = mRegistry.emplace_or_replace<MeshComponent>(OneLevel.mAsset1.entity);
	lComponent1.AddVertices(std::move(OneLevel.mAsset1.meshInfo.vertices));
	lComponent1.AddIndices(std::move(OneLevel.mAsset1.meshInfo.indices));
	mLevels.push_back(OneLevel);
}
