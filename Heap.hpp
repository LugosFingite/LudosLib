#pragma once

#include "Array.hpp"
#include "Utility.hpp"
#include "Exceptions.hpp"


namespace LudosLib
{
	namespace DataStructs
	{
		template <typename T, typename cmp_t = Lesser<T>>
		class Heap
		{
			DynamicArray<T> m_storage;
			cmp_t m_cmp;

		public:
			Heap() { static_assert(inheritancecheck<SingleCmp<T>, cmp_t>()); }

			void Push(T value)
			{
				m_storage.Append(value);
				size_t i = m_storage.Size();

				while (i != 1 && m_cmp(m_storage[i - 1], m_storage[i / 2 - 1]))
				{
					swap(m_storage[i - 1], m_storage[i / 2 - 1]);
					i /= 2;
				}
			}

			void Pop()
			{
				m_storage[0] = m_storage[m_storage.Size() - 1];
				m_storage.Remove();
				size_t i = 1, s = m_storage.Size();

				while (i * 2 <= s)
				{
					size_t next = i * 2;
					if (next < s && m_cmp(m_storage[next], m_storage[next - 1]))
						next++;

					if (m_cmp(m_storage[next - 1], m_storage[i - 1]))
					{
						swap(m_storage[next - 1], m_storage[i - 1]);
						i = next;
					}
					else i = s;
				}
			}

			size_t Size() { return m_storage.Size(); }
			bool Empty() { return m_storage.Empty(); }

			T Top() const
			{
				if (!m_storage.Empty())
					return m_storage[0];
				throw EmptyContainerError("Trying to access elements in an empty container");
			}
		};
	}
}