#pragma once

#include "Exceptions.hpp"
#include "Utility.hpp"


namespace LudosLib
{
	template <typename T, size_t size>
	class Array
	{
		T m_storage[size];

	public:
		Array(T value = T())
		{
			for (T& i : m_storage)
				i = value;
		}

		Array(const Array &other)
		{
			copy(m_storage, other.m_storage, size);
		}

		Array &operator =(const Array &other)
		{
			copy(m_storage, other.m_storage, size);
			return *this;
		}

		T &operator [](size_t index)
		{
			if (index < size)
				return m_storage[index];
			throw InvalidAccess("Trying to access elements outside the allocated memory");
		}

		T operator [](size_t index) const
		{
			if (index < size)
				return m_storage[index];
			throw InvalidAccess("Trying to access elements outside the allocated memory");
		}

		size_t Size() const { return size; }

		T *begin() { return m_storage; }
		T *end() { return (m_storage + size); }
		const T *begin() const { return m_storage; }
		const T *end() const { return (m_storage + size); }

		void Reverse()
		{
			reverse(m_storage, size);
		}
	};

	template <typename T>
	class DynamicArray
	{
		T *m_storage;
		size_t m_size = 0, m_allocated = 0;

	public:
		DynamicArray() : m_storage(new T[1]), m_size(0), m_allocated(1) {}
		~DynamicArray() { delete[] m_storage; }

		DynamicArray(const DynamicArray &other) : m_storage(new T[other.m_size]), m_size(other.m_size), m_allocated(other.m_allocated)
		{
			copy(m_storage, other.m_storage, m_size);
		}

		DynamicArray(size_t s, T value) : m_storage(new T[s]), m_size(s), m_allocated(s)
		{
			for (size_t i = 0; i < s; i++)
				m_storage[i] = value;
		}

		DynamicArray &operator =(const DynamicArray &other)
		{
			if (other.m_size > m_allocated)
				Reserve(other.m_size - m_size);
			m_size = other.m_size;

			copy(m_storage, other.m_storage, m_size);
			return *this;
		}

		T &operator [](size_t index)
		{
			if (index < m_size)
				return m_storage[index];
			throw InvalidAccess("Trying to access elements outside the allocated memory");
		}

		T operator [](size_t index) const
		{
			if (index < m_size)
				return m_storage[index];
			throw InvalidAccess("Trying to access elements outside the allocated memory");
		}

		void Reserve(size_t s)
		{
			if (m_size + s > m_allocated)
			{
				m_allocated = m_size + s;

				T *old = m_storage;
				m_storage = new T[m_allocated];

				copy(m_storage, old, m_size);
				delete[] old;
			}
		}

		void Append(T value)
		{
			if (m_size == m_allocated)
				Reserve(m_allocated);
			m_storage[m_size++] = value;
		}

		void Insert(T value, size_t index)
		{
			if (index > m_size)
				throw InvalidAccess("Trying to insert in unallocated memory");
			else
			{
				if (m_size == m_allocated)
					Reserve(m_allocated);

				T *tempStock = new T[m_size - index];
				copy(tempStock, m_storage + index, m_size - index);
				m_storage[index] = value;
				copy(m_storage + index + 1, tempStock, m_size - index);

				delete[] tempStock;
				m_size++;
			}
		}

		void Remove(size_t amount = 1) //Won't remove anything and will throw an error if trying to remove more elements than stored
		{
			if (amount > m_size)
				throw EmptyContainerError("Removing too much elements");
			else
				m_size -= amount;
		}

		size_t Size() const { return m_size; }
		bool Empty() const { return !m_size; }

		T *begin() { return m_storage; }
		T *end() { return (m_storage + m_size); }
		const T *begin() const { return m_storage; }
		const T *end() const { return (m_storage + m_size); }
	};
}