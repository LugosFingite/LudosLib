#pragma once

#include <stdexcept>


namespace LudosLib
{
	class InvalidAccess : std::runtime_error
	{
	public:
		InvalidAccess(const char* why);
	};

	class EmptyContainerError : std::runtime_error
	{
	public:
		EmptyContainerError(const char* why);
	};
}