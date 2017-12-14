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
			Array<T, size> storage;
			size_t fill = 0;

		public:
			void Push(T value)
			{
				storage[fill] = value;
				fill++;
			}

			void Pop(size_t amount = 1) //Won't remove anything and will throw an error if trying to remove more elements than stored
			{
				if (amount > fill)
					throw EmptyContainerError("Trying to remove from empty container");
				else
					fill -= amount;
			}

			size_t Size() const { return fill; }
			bool Empty() const { return !fill; }

			T Top() const { return storage[fill - 1]; }
		};

		template <typename T>
		class Stack
		{
			ChainNode<T> *top = nullptr;
			size_t size = 0;

		public:
			~Stack() //Yum ugly Destructor
			{
				while (top)
				{
					ChainNode<T> *old = top;
					top = top->previous;
					delete old;
				}
			}

			void Push(T value)
			{
				if (size == 0)
					top = new ChainNode<T>(value);
				else
				{
					top->next = new ChainNode<T>(value);
					top->next->previous = top;
					top = top->next;
				}

				size++;
			}

			void Pop(size_t amount = 1) //Won't remove anything and will throw an error if trying to remove more elements than stored
			{
				if (amount > size)
					throw EmptyContainerError("Trying to remove from empty container");
				else
				{
					for (size_t i = 0; i < amount; i++)
					{
						top = top->previous;
						delete top->next;
					}

					size -= amount;
				}
			}

			size_t Size() const { return size; }
			bool Empty() const { return !size; }

			const T& Top() const
			{
				if (size > 0)
					return *top->data;
				throw EmptyContainerError("Trying to access elements in an empty container");
			}
		};
	}
}