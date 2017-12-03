#pragma once

#include <stdexcept>


namespace LudosLib
{
	class InvalidAccess : std::runtime_error			//An exception for out-of-bound array access
	{
	public:
		InvalidAccess(const char* why);
	};
}