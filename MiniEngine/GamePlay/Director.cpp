#include "pch.h"
#include "Director.h"

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
	 

	mLevels.push_back(OneLevel);
}
