#pragma once

#include <type_traits>
#include <cstdlib>


namespace LudosLib
{
	template <typename T1, typename T2>
	struct Cmp { virtual bool operator ()(const T1 &a, const T2 &b) const = 0; };

	template <typename T>
	using SingleCmp = Cmp<T, T>;

	template <typename T>
	struct Lesser : SingleCmp<T> {
		bool operator ()(const T &a, const T &b) const override { return (a < b); }
	};

	template <typename T>
	struct Greater : SingleCmp<T> {
		bool operator ()(const T &a, const T &b) const override { return (a > b); }
	};

	template <typename T1, typename T2>
	struct Pair
	{
		Pair(T1 a, T2 b) : first(a), second(b) {}
		Pair(const Pair &other) : first(other.first), second(other.second) {}
		Pair &operator =(const Pair &other) { first = other.first; second = other.second; return *this; }

		bool operator ==(const Pair &other) const { return (first == other.first && second == other.second); }
		bool operator !=(const Pair &other) const { return  (first != other.first || second != other.second); }
		bool operator <(const Pair &other) const { return (first == other.first ? second < other.second : first < other.first); }
		bool operator <=(const Pair &other) const { return (first == other.first ? second <= other.second : first < other.first); }
		bool operator >(const Pair &other) const { return (first == other.first ? second > other.second : first > other.first); }
		bool operator >=(const Pair &other) const { return (first == other.first ? second >= other.second : first > other.first); }

		T1 first; T2 second;
	};

	template <typename T>
	struct SinglePair : Pair<T, T> { SinglePair(T x) : first(x), second(x) {} };

	
	template <typename T>
	void swap(T &a, T &b)
	{
		T temp = a;
		a = b; b = temp;
	}

	template <typename T>
	void copy(T *object, const T *original, size_t copyLength)
	{
		for (size_t i = 0; i < copyLength; i++)
			object[i] = original[i];
	}

	template <typename T>
	void reverse(T *object, size_t size)
	{
		for (size_t i = 0; i < size--; i++)
			swap(object[i], object[size]);
	}

	template <typename Base, typename T>
	constexpr bool inheritancecheck() { return std::is_base_of<Base, T>::value; }


	namespace DataStructs
	{
		template <typename T>
		struct ChainNode
		{
			ChainNode(T value) : data(value) {}
			~ChainNode()
			{
				if (previous != nullptr && previous->next == this)
					delete previous;
				if (next != nullptr && next->previous == this)
					delete next;
				previous = next = nullptr;
			}

			T data;
			ChainNode *previous = nullptr, *next = nullptr;
		};
		
		template <typename T>
		struct AVLNode
		{
			AVLNode(T value) : data(value) {}
			~AVLNode()
			{
				delete left; delete right;
				left = right = nullptr;
			}

			T data;
			size_t size = 1, height = 1;
			AVLNode *left = nullptr, *right = nullptr;
		};
	}
}