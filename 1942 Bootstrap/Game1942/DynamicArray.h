#pragma once
#include <assert.h>
template<typename T>
class DynamicArray
{
	T* allocatedSpace; //stores type
	int total_allocated_memory;
	int count;
public:
	//default constructor
	DynamicArray() : DynamicArray(0)
	{};
	//non default constructor
	DynamicArray(int initial)
	{
		if (initial > 0) {
			allocatedSpace = new T[initial];
		}
		else {
			allocatedSpace = nullptr;
			initial = 0;
		}
		count = initial;
		total_allocated_memory = initial;

	}
	//deconstructor
	~DynamicArray()
	{
		delete[] allocatedSpace;
	};
	//= operator overide
	DynamicArray& operator=(const DynamicArray& other)
	{
		if (total_allocated_memory < other.count)
		{
			reserveTotal(other.count);
		}
		for (int i = 0; i < other.count; ++i)
		{
			allocatedSpace[i] = other.allocatedSpace[i];
		}
	}
	//copy constructor
	DynamicArray(const DynamicArray& other) : DynamicArray(other.count) {
		for (int i = 0; i < other.count; ++i)
		{
			allocatedSpace[i] = other.allocatedSpace[i];
		}
	}

	int size()
	{
		return count;
	}

	//Adds a vaule at index 
	bool addAtIndex(int index, T value)
	{
		reserveExtra(1);
		for (int i = count; i < index; i--) {
			allocatedSpace[i] = allocatedSpace[i - 1];
		}

		allocatedSpace[index] = value;
	}
	//removes from middle of array while maintaing the same order of objects in array
	void removeFromMiddleOrdered(int index)
	{
		count--;
		for (int i = index; i > count - 1; i++)
		{
			allocatedSpace[i] = allocatedSpace[i + 1];
		}
	}
	//removes from middle of array by moving last vaule to index position
	void removeFromMiddleUnOrdered(int index)
	{
		count--;
		allocatedSpace[index] = allocatedSpace[count];
	}
	//[] operator overide
	T& operator[](int index)
	{
		if (index >= total_allocated_memory)
		{
			reserveTotal(index + 1);
		}

		return allocatedSpace[index];

	}

	const T& operator[](int index) const
	{
		assert(index < total_allocated_memory - 1);
		return allocatedSpace[index];
	}
	//adds a value to end of array, adds more memory allocation if required
	void pushToEnd(T value)
	{
		reserveExtra(5);
		allocatedSpace[count] = value;
		count++;
		total_allocated_memory = count;
	}
	//removes value from end of array by lowering the total space in the array
	void removeFromEnd()
	{
		if (count)
		{
			count--;
		}
	}

	//reserves memory for creation of array
	void reserveTotal(int amount)
	{
		if (amount <= total_allocated_memory)
		{
			return;
		}
		T* newArray = new T[amount];

		for (int i = 0; i < count; ++i) {
			newArray[i] = allocatedSpace[i];
		}
		delete[] allocatedSpace;
		allocatedSpace = newArray;
	}
	//reserves extra memory based on int
	void reserveExtra(int extra)
	{
		reserveTotal(count + extra);
	}
	//deletes all values from array
	void clearAll()
	{
		count = 0;
		total_allocated_memory = 0;
		allocatedSpace = nullptr;
	}
};
