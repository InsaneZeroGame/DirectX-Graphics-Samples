#include "pch.h"
#include "Level.h"

GamePlay::Level::Level()
{
	mAsset.meshInfo.vertices = {
		{0.0,1.0,0.0,1.0},
		{1.0,0.0,0.0,1.0},
		{-1.0,0.0,0.0,1.0},
		};

	mAsset1.meshInfo.vertices = {
		{0.0,-1.0,0.0,1.0},
		{-1.0,0.0,0.0,1.0},
		{1.0,0.0,0.0,1.0},

	};

	mAsset1.meshInfo.indices = { 0,1,2 };
	mAsset.meshInfo.indices = {0,1,2};

}

GamePlay::Level::~Level()
{

}

void GamePlay::Level::Tick(float ms)
{
}
