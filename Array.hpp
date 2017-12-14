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
			for (T& i : storage)
				i = value;
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
		T *storage;
		size_t size = 0, allocated = 0;

	public:
		DynamicArray() : storage(new T[1]), size(0), allocated(1) {}
		~DynamicArray() { delete[] storage; }

		DynamicArray(const DynamicArray& other) : storage(new T[other.size]), size(other.size), allocated(other.allocated)
		{
			copy(storage, other.storage, size);
		}

		DynamicArray(size_t s, T value) : storage(new T[s]), size(s), allocated(s)
		{
			for (size_t i = 0; i < s; i++)
				storage[i] = value;
		}

		DynamicArray& operator =(const DynamicArray& other)
		{
			if (other.size > allocated)
				Reserve(other.size - size);
			size = other.size;

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

		void Reserve(size_t s)
		{
			if (size + s > allocated)
			{
				allocated = size + s;

				T *old = storage;
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

		void Insert(T value, size_t index)
		{
			if (index > size)
				throw InvalidAccess("Trying to insert in unallocated memory");
			else
			{
				if (size == allocated)
					Reserve(allocated);

				T* tempStock = new T[size - index];
				copy(tempStock, storage + index, size - index);
				storage[index] = value;
				copy(storage + index + 1, tempStock, size - index);

				delete[] tempStock;
				size++;
			}
		}

		void Remove(size_t amount = 1) //Won't remove anything and will throw an error if trying to remove more elements than stored
		{
			if (amount > size)
				throw EmptyContainerError("Removing too much elements");
			else
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