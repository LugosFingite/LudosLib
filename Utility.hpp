#pragma once


namespace LudosLib
{
	template <typename T>
	void swap(T& a, T& b)
	{
		T temp = a;
		a = b; b = temp;
	}

	template <typename T>
	void copy(T* object, const T* original, size_t copyLength)
	{
		for (size_t i = 0; i < copyLength; i++)
			object[i] = original[i];
	}

	template <typename T>
	void reverse(T* object, size_t size)
	{
		for (size_t i = 0; i < size--; i++)
			swap(object[i], object[size]);
	}

	namespace DataStructs
	{
		template <typename T>
		struct ChainNode
		{
			ChainNode(T value) : data(new T(value)) {}
			~ChainNode() { delete data; }
			
			T *data;
			ChainNode *previous = nullptr, *next = nullptr;
		};
	}
}