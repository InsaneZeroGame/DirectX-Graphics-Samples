#pragma once
#include <entt/entt.hpp>

namespace Interface
{
	class System
	{
	public:
		System();

		virtual ~System();

		static  entt::registry& GetGlobalRegistry();
	protected:

		static entt::registry mRegistry;
	private:
	};
}

