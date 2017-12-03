#pragma once

#include "Exceptions.hpp"
#include "Utility.hpp"


namespace LudosLib
{
	template <typename T, size_t size>
	class Array
	{
		T storage[size];

	public:
		Array()						//Default Constructor
		{
			for (size_t i = 0; i < size; i++)
				storage[i] = T();
		}

		Array(T value)					//Fill constructor
		{
			for (size_t i = 0; i < size; i++)
				storage[i] = value;
		}

		Array(const Array& other)			//Copy Constructor
		{
			copy(storage, other.storage, size);
		}

		void operator =(const Array& other)		//Copy
		{
			copy(storage, other.storage, size);
		}

		T& operator [](size_t index)			//Element access
		{
			if (index < size)
				return storage[index];
			throw InvalidAccess("Trying to access elements outside the allocated memory");
		}

		T operator [](size_t index) const		//Element access (constant)
		{
			if (index < size)
				return storage[index];
			throw InvalidAccess("Trying to access elements outside the allocated memory");
		}

		size_t Size() const { return size; }		//Not especially useful but still

		const T* begin() const { return storage; }
		const T* end() const { return (storage + size); }

		void Reverse()
		{
			reverse(storage, size);
		}
	};
}
