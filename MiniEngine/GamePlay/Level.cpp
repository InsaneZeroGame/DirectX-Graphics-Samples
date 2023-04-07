#include "pch.h"
#include "Level.h"

GamePlay::Level::Level()
{
	mAsset.meshInfo.vertices = {
		{0.0,1.0,0.0,1.0},
		{1.0,0.0,0.0,1.0},
		{-1.0,0.0,0.0,1.0},
		};

}

GamePlay::Level::~Level()
{

}

void GamePlay::Level::Tick(float ms)
{
}
