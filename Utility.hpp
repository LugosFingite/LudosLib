#pragma once


namespace LudosLib
{
	template <typename T>
	void swap(T& a, T& b)												//Swaps 2 values
	{
		T temp = a;
		a = b; b = temp;
	}

	template <typename T>
	void copy(T* object, const T* original, size_t copyLength)			//Copies the content of list B to list A
	{
		for (size_t i = 0; i < copyLength; i++)
			object[i] = original[i];
	}

	template <typename T>
	void reverse(T* object, size_t size)								//Reverses a list
	{
		for (size_t i = 0; i < --size; i++) //Ugly ass for... x)
			swap(object[i], object[size]);
	}
}