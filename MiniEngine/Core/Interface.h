#pragma once

namespace Interface
{
	class Tickable
	{
	public:
		Tickable();

		virtual ~Tickable();

		virtual void Tick(float ms) = 0;

	private:

	};
}




