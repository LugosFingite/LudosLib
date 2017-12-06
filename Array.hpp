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
		Array(T value = T())
		{
			for (size_t i = 0; i < size; i++)
				storage[i] = value;
		}

		Array(const Array& other)
		{
			copy(storage, other.storage, size);
		}

		Array& operator =(const Array& other)
		{
			copy(storage, other.storage, size);
			return *this;
		}

		T& operator [](size_t index)
		{
			if (index < size)
				return storage[index];
			throw InvalidAccess("Trying to access elements outside the allocated memory");
		}

		T operator [](size_t index) const
		{
			if (index < size)
				return storage[index];
			throw InvalidAccess("Trying to access elements outside the allocated memory");
		}

		size_t Size() const { return size; }

		T* begin() { return storage; }
		T* end() { return (storage + size); }
		const T* begin() const { return storage; }
		const T* end() const { return (storage + size); }

		void Reverse()
		{
			reverse(storage, size);
		}
	};

	template <typename T>
	class DynamicArray
	{
		T* storage;
		size_t size = 0, allocated = 0;

	public:
		DynamicArray() : storage(new T[1]), size(0), allocated(1) {}

		T& operator [](size_t index)
		{
			if (index < size)
				return storage[index];
			throw InvalidAccess("Trying to access elements outside the allocated memory");
		}

		T operator [](size_t index) const
		{
			if (index < size)
				return storage[index];
			throw InvalidAccess("Trying to access elements outside the allocated memory");
		}

		void Reserve(size_t s)
		{
			if (size + s > allocated)
			{
				allocated = size + s;

				T* old = storage;
				storage = new T[allocated];

				copy(storage, old, size);
				delete[] old;
			}
		}

		void Append(T value)
		{
			if (size == allocated)
				Reserve(allocated);
			storage[size++] = value;
		}

		void Remove(size_t amount = 1)
		{
			if (amount > size)
				throw InvalidAccess("Removing too much elements");
			size -= amount;
		}

		size_t Size() const { return size; }
		bool Empty() const { return !size; }

		T* begin() { return storage; }
		T* end() { return (storage + size); }
		const T* begin() const { return storage; }
		const T* end() const { return (storage + size); }
	};
}