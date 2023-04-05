#pragma once
#include <Core/System.h>
#include <mutex>
#include "Level.h"

namespace GamePlay
{
	class Director : public Interface::System
	{
	public:

		virtual ~Director();

		static Director& GetDirector();

		void LoadLevel();

	private:

		Director();

		static Director mInstance;

		static std::once_flag mCallOnce;

		std::vector<Level> mLevels;
	};
	
}


