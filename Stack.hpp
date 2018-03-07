#pragma once

#include "Array.hpp"
#include "Utility.hpp"
#include "Exceptions.hpp"


namespace LudosLib
{
	namespace DataStructs
	{
		template <typename T, size_t size>
		class StaticStack
		{
			Array<T, size> m_storage;
			size_t m_fill = 0;

		public:
			void Push(T value)
			{
				m_storage[m_fill] = value;
				m_fill++;
			}

			void Pop(size_t amount = 1) //Won't remove anything and will throw an error if trying to remove more elements than stored
			{
				if (amount > m_fill)
					throw EmptyContainerError("Trying to remove from empty container");
				else
					m_fill -= amount;
			}

			size_t Size() const { return m_fill; }
			bool Empty() const { return !m_fill; }

			T Top() const { return m_storage[m_fill - 1]; }
		};

		template <typename T>
		class Stack
		{
			ChainNode<T> *m_top = nullptr;
			size_t m_size = 0;

		public:
			~Stack() { delete m_top; }

			void Push(T value)
			{
				if (Empty())
					m_top = new ChainNode<T>(value);
				else
				{
					m_top->next = new ChainNode<T>(value);
					m_top->next->previous = m_top;
					m_top = m_top->next;
				}

				m_size++;
			}

			void Pop(size_t amount = 1) //Won't remove anything and will throw an error if trying to remove more elements than stored
			{
				if (amount > m_size)
					throw EmptyContainerError("Trying to remove from empty container");
				else
				{
					for (size_t i = 0; i < amount; i++)
					{
						m_top = m_top->previous;
						delete m_top->next;
					}

					m_size -= amount;
				}
			}

			size_t Size() const { return m_size; }
			bool Empty() const { return !m_size; }

			T Top() const
			{
				if (m_size > 0)
					return m_top->data;
				throw EmptyContainerError("Trying to access elements in an empty container");
			}
		};
	}
}