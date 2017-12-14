#include "Exceptions.hpp"


namespace LudosLib
{
	InvalidAccess::InvalidAccess(const char* why) : std::runtime_error(why) {}
	EmptyContainerError::EmptyContainerError(const char* why) : std::runtime_error(why) {}
}