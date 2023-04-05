#include "pch.h"
#include "System.h"

entt::registry Interface::System::mRegistry;

Interface::System::System()
{

}

Interface::System::~System()
{

}

entt::registry& Interface::System::GetGlobalRegistry()
{
	return mRegistry;
}
